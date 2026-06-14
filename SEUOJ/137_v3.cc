#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <functional>
#include <cmath>
using namespace std;

struct Point3D {
    long long x, y, z;
};

struct Box {
    int id;
    long long l, w, h;
    long long vol;
};

struct Item {
    int id;
    long long l, w, h;
    int allowRotate;
    long long vol;
};

struct PlacedItem {
    int id;
    long long px, py, pz;
    long long sl, sw, sh;
};

vector<Point3D> getValidRotations(const Item& item) {
    vector<Point3D> rotations;
    rotations.push_back({item.l, item.w, item.h});
    if (item.l != item.w) {
        rotations.push_back({item.w, item.l, item.h});
    }
    if (item.allowRotate == 1) {
        rotations.push_back({item.w, item.h, item.l});
        rotations.push_back({item.h, item.w, item.l});
        rotations.push_back({item.l, item.h, item.w});
        rotations.push_back({item.h, item.l, item.w});
    }
    return rotations;
}

bool isCollision(const PlacedItem& a, const PlacedItem& b) {
    bool disjointX = (a.px + a.sl <= b.px) || (b.px + b.sl <= a.px);
    bool disjointY = (a.py + a.sw <= b.py) || (b.py + b.sw <= a.py);
    bool disjointZ = (a.pz + a.sh <= b.pz) || (b.pz + b.sh <= a.pz);
    return !disjointX && !disjointY && !disjointZ;
}

bool isPointInsideAnyItem(const Point3D& pt, const vector<PlacedItem>& placedResults) {
    for (const auto& item : placedResults) {
        if (pt.x >= item.px && pt.x < item.px + item.sl &&
            pt.y >= item.py && pt.y < item.py + item.sw &&
            pt.z >= item.pz && pt.z < item.pz + item.sh) {
            return true;
        }
    }
    return false;
}

void updateEPList(vector<Point3D>& epList, const PlacedItem& newItem,
                  const vector<PlacedItem>& placedResults) {
    Point3D pRight = {newItem.px + newItem.sl, newItem.py, newItem.pz};
    Point3D pFront = {newItem.px, newItem.py + newItem.sw, newItem.pz};
    Point3D pTop   = {newItem.px, newItem.py, newItem.pz + newItem.sh};

    epList.push_back(pRight);
    epList.push_back(pFront);
    epList.push_back(pTop);

    vector<Point3D> validEPs;
    for (const auto& ep : epList) {
        if (!isPointInsideAnyItem(ep, placedResults)) {
            validEPs.push_back(ep);
        }
    }

    sort(validEPs.begin(), validEPs.end(), [](const Point3D& a, const Point3D& b) {
        if (a.z != b.z) return a.z < b.z;
        if (a.y != b.y) return a.y < b.y;
        return a.x < b.x;
    });

    validEPs.erase(unique(validEPs.begin(), validEPs.end(),
        [](const Point3D& a, const Point3D& b) {
            return a.x == b.x && a.y == b.y && a.z == b.z;
        }), validEPs.end());

    epList = validEPs;
}

bool packBox(const Box& box, const vector<Item>& items,
             vector<PlacedItem>& placedResults) {
    vector<Point3D> epList;
    epList.push_back({0, 0, 0});
    placedResults.clear();

    for (const auto& item : items) {
        bool isPlaced = false;
        Point3D bestEP = {-1, -1, -1};
        Point3D bestSize = {-1, -1, -1};
        long long bestZ = 1e18, bestY = 1e18, bestX = 1e18;

        vector<Point3D> rotations = getValidRotations(item);

        for (const auto& ep : epList) {
            for (const auto& rot : rotations) {
                if (ep.x + rot.x > box.l ||
                    ep.y + rot.y > box.w ||
                    ep.z + rot.z > box.h) {
                    continue;
                }

                PlacedItem temp = {item.id, ep.x, ep.y, ep.z,
                                   rot.x, rot.y, rot.z};
                bool collide = false;
                for (const auto& alreadyPlaced : placedResults) {
                    if (isCollision(temp, alreadyPlaced)) {
                        collide = true;
                        break;
                    }
                }
                if (collide) continue;

                if (ep.z < bestZ ||
                   (ep.z == bestZ && ep.y < bestY) ||
                   (ep.z == bestZ && ep.y == bestY && ep.x < bestX)) {
                    bestZ = ep.z; bestY = ep.y; bestX = ep.x;
                    bestEP = ep;
                    bestSize = rot;
                    isPlaced = true;
                }
            }
        }

        if (!isPlaced) return false;

        PlacedItem finalPlacement = {
            item.id,
            bestEP.x, bestEP.y, bestEP.z,
            bestSize.x, bestSize.y, bestSize.z
        };
        placedResults.push_back(finalPlacement);
        updateEPList(epList, finalPlacement, placedResults);
    }
    return true;
}

bool cmpVolume(const Item& a, const Item& b) {
    return a.vol > b.vol;
}

bool cmpBaseArea(const Item& a, const Item& b) {
    return (a.l * a.w) > (b.l * b.w);
}

bool cmpHeight(const Item& a, const Item& b) {
    return a.h > b.h;
}

bool cmpLongestSide(const Item& a, const Item& b) {
    long long maxA = max({a.l, a.w, a.h});
    long long maxB = max({b.l, b.w, b.h});
    return maxA > maxB;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    if (!(cin >> m >> n)) return 0;

    vector<Box> boxes(m);
    for (int i = 0; i < m; ++i) {
        boxes[i].id = i + 1;
        cin >> boxes[i].l >> boxes[i].w >> boxes[i].h;
        boxes[i].vol = boxes[i].l * boxes[i].w * boxes[i].h;
    }

    vector<Item> items(n);
    long long totalItemVol = 0;
    for (int i = 0; i < n; ++i) {
        items[i].id = i + 1;
        cin >> items[i].l >> items[i].w >> items[i].h >> items[i].allowRotate;
        items[i].vol = items[i].l * items[i].w * items[i].h;
        totalItemVol += items[i].vol;
    }

    sort(boxes.begin(), boxes.end(),
         [](const Box& a, const Box& b) { return a.vol < b.vol; });

    auto startTime = chrono::steady_clock::now();
    const double TIME_LIMIT = 5.0;  // 给充分时间尝试所有箱子

    int bestBoxIdx = -1;
    vector<PlacedItem> bestPlan;
    double bestScore = -1;

    mt19937 rng(42);
    vector<function<bool(const Item&, const Item&)>> strategies = {
        cmpVolume, cmpBaseArea, cmpHeight, cmpLongestSide
    };
    for (int i = 0; i < m; ++i) {
        if (totalItemVol > boxes[i].vol) continue;

        vector<PlacedItem> currentPlan;
        bool found = false;

        for (auto& strategy : strategies) {
            auto now = chrono::steady_clock::now();
            double elapsed = chrono::duration<double>(now - startTime).count();
            if (elapsed >= TIME_LIMIT) break;

            vector<Item> temp = items;
            sort(temp.begin(), temp.end(), strategy);
            if (packBox(boxes[i], temp, currentPlan)) {
                found = true;
                break;
            }
        }
        if (!found) {
            vector<Item> shuffled = items;
            while (true) {
                auto now = chrono::steady_clock::now();
                double elapsed = chrono::duration<double>(now - startTime).count();
                if (elapsed >= TIME_LIMIT) break;

                shuffle(shuffled.begin(), shuffled.end(), rng);
                if (packBox(boxes[i], shuffled, currentPlan)) {
                    found = true;
                    break;
                }
            }
        }
        if (found) {
            auto now = chrono::steady_clock::now();
            double runtimeMs = chrono::duration<double, milli>(now - startTime).count();

            double Tc = max(20.0, runtimeMs);
            double St = min(200.0, 100.0 * sqrt(Tc / 20.0));
            double Sq = 100.0 * totalItemVol / boxes[i].vol;
            double score = 0.65 * Sq + 0.35 * St;
            if (score > bestScore) {
                bestScore = score;
                bestBoxIdx = i;
                bestPlan = currentPlan;
            }
        }
    }

    if (bestBoxIdx == -1) {
        cout << "DORAYAKI\n";
        return 0;
    }

    cout << boxes[bestBoxIdx].id << "\n";
    sort(bestPlan.begin(), bestPlan.end(),
         [](const PlacedItem& a, const PlacedItem& b) { return a.id < b.id; });
    for (const auto& p : bestPlan) {
        cout << p.px << " " << p.py << " " << p.pz << " "
             << p.sl << " " << p.sw << " " << p.sh << "\n";
    }

    return 0;
}
