#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//三维坐标点
struct Point3D {
    long long x, y, z;
};

//候选箱子
struct Box{
    int id;
    long long l,w,h;
    long long vol;
};

//候选道具
struct Item{
    int id; 
    long long l, w, h;
    int allowRotate; // 0 或 1
    long long vol; 
};

// 4. 记录道具放在箱子里的最终状态（用于输出）
struct PlacedItem {
    int id;
    long long px, py, pz; // 放在箱子里的坐标（即使用的极端点）
    long long sl, sw, sh; // 摆放后的实际长宽高（对应各种旋转）
};

// 获取一个道具所有可能的摆放尺寸
vector<Point3D> getValidRotations(const Item& item) {
    vector<Point3D> rotations;

    rotations.push_back({item.l, item.w, item.h});
    // 底面旋转90度
    if (item.l != item.w) {
        rotations.push_back({item.w, item.l, item.h});
    }

    // 如果允许放倒，额外增加 4 种状态
    if (item.allowRotate == 1) {
        rotations.push_back({item.w, item.h, item.l});
        rotations.push_back({item.h, item.w, item.l});
        rotations.push_back({item.l, item.h, item.w});
        rotations.push_back({item.h, item.l, item.w});
    }
    
    return rotations;
}

// 判断两个已经确定起始点和尺寸的道具是否重叠（碰撞）
bool isCollision(const PlacedItem& a, const PlacedItem& b) {

    // A在B的左边，或者 B在A的左边
    bool disjointX = (a.px + a.sl <= b.px) || (b.px + b.sl <= a.px);
    
    // A在B的后面，或者 B在A的后面
    bool disjointY = (a.py + a.sw <= b.py) || (b.py + b.sw <= a.py);
    
    // A在B的下面，或者 B在A的下面
    bool disjointZ = (a.pz + a.sh <= b.pz) || (b.pz + b.sh <= a.pz);
    // 如果三个维度都没有错开，说明发生了碰撞
    if (!disjointX && !disjointY && !disjointZ) {
        return true; // 发生碰撞
    }
    return false; // 安全，没有碰撞
}

// 更新极端点列表（前向声明）
void updateEPList(vector<Point3D>& epList, const PlacedItem& newItem,
                   const vector<PlacedItem>& placedResults);

// 尝试将所有 items 塞进 box 里
// 如果成功，返回 true，并且 placedResults 里面装着答案；如果失败，返回 false
bool packBox(const Box& box, vector<Item> items, vector<PlacedItem>& placedResults) {
    
    // 按照体积从大到小排序
    sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        return a.vol > b.vol;
    });
   
    //初始化极端点列表，一开始只有原点
    vector<Point3D> epList;
    epList.push_back({0, 0, 0});
    
    // 清空结果
    placedResults.clear();

    // 3. 开始一件一件塞道具
    for (const auto& item : items) {
        
        bool isPlaced = false;
        Point3D bestEP = {-1, -1, -1}; // 记录最佳起始点
        Point3D bestSize = {-1, -1, -1}; // 记录最佳旋转后的尺寸
        
        // 记录最佳分数，越小越好，初始给个无穷大
        long long bestZ = 1e18, bestY = 1e18, bestX = 1e18; 
        
        // 获取这个道具所有允许的旋转状态
        vector<Point3D> rotations = getValidRotations(item);
        
        // 遍历当前所有的极端点
        for (const auto& ep : epList) {
            // 遍历所有的旋转状态
            for (const auto& rot : rotations) {
                
                // 出界了吗？（长宽高有没有超出箱子的 L, W, H）
                if (ep.x + rot.x > box.l || 
                    ep.y + rot.y > box.w || 
                    ep.z + rot.z > box.h) {
                    continue; // 超出箱子了，换下一种
                }

                // 我们构造一个临时的摆放状态，去和已经放好的道具一一对比
                PlacedItem temp = {item.id, ep.x, ep.y, ep.z, rot.x, rot.y, rot.z};
                bool collide = false;
                for (const auto& alreadyPlaced : placedResults) {
                    if (isCollision(temp, alreadyPlaced)) {
                        collide = true;
                        break;
                    }
                }
                if (collide) continue; 
                // 评价这个位置是不是“最左下后”
                if (ep.z < bestZ || 
                   (ep.z == bestZ && ep.y < bestY) || 
                   (ep.z == bestZ && ep.y == bestY && ep.x < bestX)) {
                    
                    // 找到更好的了！更新记录
                    bestZ = ep.z; bestY = ep.y; bestX = ep.x;
                    bestEP = ep;
                    bestSize = rot;
                    isPlaced = true;
                }
            }
        }
        
    
        if (!isPlaced) {
            // 说明这个箱子装不下这套道具
            return false; 
        }

        PlacedItem finalPlacement = {
            item.id, 
            bestEP.x, bestEP.y, bestEP.z, 
            bestSize.x, bestSize.y, bestSize.z
        };
        placedResults.push_back(finalPlacement);
        updateEPList(epList, finalPlacement, placedResults);
    }
    // 所有道具都成功塞进去了！
    return true;
}

// 检查某个极端点 pt 是否被吞噬（落在任何已放置的道具内部）
bool isPointInsideAnyItem(const Point3D& pt, const vector<PlacedItem>& placedResults) {
    for (const auto& item : placedResults) {
        // 范围是左闭右开
        if (pt.x >= item.px && pt.x < item.px + item.sl &&
            pt.y >= item.py && pt.y < item.py + item.sw &&
            pt.z >= item.pz && pt.z < item.pz + item.sh) {
            return true; 
        }
    }
    return false; 
}

void updateEPList(vector<Point3D>& epList, const PlacedItem& newItem, const vector<PlacedItem>& placedResults) {
    // 添加新的点
    Point3D pRight = {newItem.px + newItem.sl, newItem.py, newItem.pz};
    Point3D pFront = {newItem.px, newItem.py + newItem.sw, newItem.pz};
    Point3D pTop   = {newItem.px, newItem.py, newItem.pz + newItem.sh};

    epList.push_back(pRight);
    epList.push_back(pFront);
    epList.push_back(pTop);

    // 过滤掉所有死点
    vector<Point3D> validEPs;
    for (const auto& ep : epList) {
        // 如果这个点不在任何物体的内部，它就活下来了
        if (!isPointInsideAnyItem(ep, placedResults)) {
            validEPs.push_back(ep);
        }
    }

 
    sort(validEPs.begin(), validEPs.end(), [](const Point3D& a, const Point3D& b) {
        if (a.z != b.z) return a.z < b.z;
        if (a.y != b.y) return a.y < b.y;
        return a.x < b.x;
    });

    // 去重：多个箱子堆叠可能会在同一个坐标产生完全重合的红点
   
    validEPs.erase(unique(validEPs.begin(), validEPs.end(), [](const Point3D& a, const Point3D& b) {
        return a.x == b.x && a.y == b.y && a.z == b.z;
    }), validEPs.end());

    // 更新原本的列表
    epList = validEPs;
}



// 题目的主函数逻辑
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int m, n;
    if (!(cin >> m >> n)) return 0;

    vector<Box> boxes(m);
    for (int i = 0; i < m; ++i) {
        boxes[i].id = i + 1; // 题目箱子编号从 1 开始
        cin >> boxes[i].l >> boxes[i].w >> boxes[i].h;
        boxes[i].vol = boxes[i].l * boxes[i].w * boxes[i].h;
    }

    vector<Item> items(n);
    for (int i = 0; i < n; ++i) {
        items[i].id = i + 1; // 记录原始编号，输出时必须按原始顺序
        cin >> items[i].l >> items[i].w >> items[i].h >> items[i].allowRotate;
        items[i].vol = items[i].l * items[i].w * items[i].h;
    }

    sort(boxes.begin(), boxes.end(), [](const Box& a, const Box& b) {
        return a.vol < b.vol;
    });

    bool foundSolution = false;
    int chosenBoxId = -1;
    vector<PlacedItem> finalPlan;

    // 遍历每一个候选箱子
    for (const auto& box : boxes) {
        
        vector<PlacedItem> currentPlan;
        
        // 尝试把这批道具装进当前这口箱子
        if (packBox(box, items, currentPlan)) {
          //箱子从小到大选
            foundSolution = true;
            chosenBoxId = box.id;
            finalPlan = currentPlan;
            break; // 立刻停止尝试，省下时间赚速度分！
        }
    }
    if (!foundSolution) {
        cout << "DORAYAKI\n";
    } else {
        cout << chosenBoxId << "\n";

        sort(finalPlan.begin(), finalPlan.end(), [](const PlacedItem& a, const PlacedItem& b) {
            return a.id < b.id;
        });
        for (const auto& p : finalPlan) {
            cout << p.px << " " << p.py << " " << p.pz << " "
                 << p.sl << " " << p.sw << " " << p.sh << "\n";
        }
    }

    return 0;
}