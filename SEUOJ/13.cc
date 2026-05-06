//最大凸包问题
#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
struct Point{
    int x,y;
};
//计算叉积
int computeCrossProduct(const Point &a,const Point &b,const Point &c){
    return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);
}

int distanceToline(const Point &a,const Point &b,const Point&c){
    return abs(computeCrossProduct(a,b,c))/sqrt(pow(b.x-a.x,2)+pow(b.y-a.y,2));
}

bool isRightof(const Point &a,const Point &b,const Point &c){
    return computeCrossProduct(a,b,c)<0;
}

//部分快速凸包的实现算法
vector<Point> quick_half_hull(vector<Point>& S,Point & a,Point & b){
    if(S.empty()) return {};
    int dismax=-1;
    Point dispoint;
    //先遍历找到AB外侧最远端的点，一定是凸包边缘上的点
    for(const auto &p:S){
        if(isRightof(a,b,p)){
            int crossArea=abs(computeCrossProduct(a,b,p));
            if(crossArea>dismax){
                dismax=crossArea;
                dispoint=p;
            }
        }
    }
    //找到了最远点 dispoint后，继续递归寻找dispoint与a和b之间的点
    //筛选出外部的点集
    if (dismax <= 0) return {};
    vector<Point>A,B;
    for(const auto & point:S){
        if(isRightof(a,dispoint,point)){
            A.push_back(point);
        }else if(isRightof(dispoint,b,point)){
            B.push_back(point);
        }
    }

    //对外部点集的递归调用
    vector<Point> QA=quick_half_hull(A,a,dispoint);
    vector<Point> QB=quick_half_hull(B,dispoint,b);
    //合并结果
    vector<Point> res;
    //先插入QA
    res.insert(res.end(), QA.begin(), QA.end());
    //再插入当前新找到的点
    res.push_back(dispoint);
    //最后插入QB
    res.insert(res.end(), QB.begin(), QB.end());
    return res;
}


bool ComparePoint(const Point &a,const Point &b){
    if(a.y!=b.y){
        return a.y<b.y;
    }
    return a.x<b.x;
}

//完整的快速凸包算法
    vector<Point> quick_hull(vector<Point> S){
        //先找到最远的两个点，作为凸包的两个端点
        sort(S.begin(),S.end(),ComparePoint);
        //去重
        S.erase(unique(S.begin(), S.end(), [](const Point& p1, const Point& p2) {
        return p1.x == p2.x && p1.y == p2.y;
    }), S.end());
        if(S.size()<=2) return S;
        Point a=S[0];
        Point b=S[S.size()-1];

        vector<Point> A,B;
        for(const auto& point:S){
            if(isRightof(a,b,point)){
                A.push_back(point);
            }else if(isRightof(b,a,point)){
                B.push_back(point);
            }
        }

        vector<Point> QA=quick_half_hull(A,a,b);
        vector<Point> QB=quick_half_hull(B,b,a);
        vector<Point> res;
        res.push_back(a);
        res.insert(res.end(), QA.begin(), QA.end());
        res.push_back(b);
        res.insert(res.end(), QB.begin(), QB.end());
        return res;

    }

    int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;

    if (cin >> t) {
        for (int i = 1; i <= t; ++i) {
            int n;
            cin >> n;
            vector<Point> points(n);
            for (int j = 0; j < n; ++j) {
                cin >> points[j].x >> points[j].y;
            }
            vector<Point> hull = quick_hull(points);
            cout << "case " << i << ":" << "\n";
            for (const auto& p : hull) {
                cout << p.x << " " << p.y << "\n";
            }
        }
    }
    return 0;
}