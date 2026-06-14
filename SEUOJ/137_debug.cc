#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define DEBUG 1

struct Point3D { long long x, y, z; };
struct Box { int id; long long l,w,h; long long vol; };
struct Item { int id; long long l, w, h; int allowRotate; long long vol; };
struct PlacedItem { int id; long long px, py, pz, sl, sw, sh; };

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

void updateEPList(vector<Point3D>& epList, const PlacedItem& newItem, const vector<PlacedItem>& placedResults);

bool packBox(const Box& box, vector<Item> items, vector<PlacedItem>& placedResults) {
    sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        return a.vol > b.vol;
    });

    vector<Point3D> epList;
    epList.push_back({0, 0, 0});
    placedResults.clear();

#if DEBUG
    cerr << "\n=== packBox: Box " << box.id << " (" << box.l << "x" << box.w << "x" << box.h << ") vol=" << box.vol << " ===\n";
    cerr << "Items sorted by volume (desc):\n";
    for (auto& it : items) cerr << "  id=" << it.id << " " << it.l << "x" << it.w << "x" << it.h << " vol=" << it.vol << " rot=" << it.allowRotate << "\n";
#endif

    int step = 0;
    for (const auto& item : items) {
        step++;
        bool isPlaced = false;
        Point3D bestEP = {-1, -1, -1};
        Point3D bestSize = {-1, -1, -1};
        long long bestZ = 1e18, bestY = 1e18, bestX = 1e18;

        vector<Point3D> rotations = getValidRotations(item);

#if DEBUG
        cerr << "\n--- Step " << step << ": Placing item id=" << item.id << " orig=(" << item.l << "," << item.w << "," << item.h << ") vol=" << item.vol << " ---\n";
        cerr << "  Valid rotations (" << rotations.size() << "):";
        for (auto& r : rotations) cerr << " (" << r.x << "," << r.y << "," << r.z << ")";
        cerr << "\n";
        cerr << "  EP list (" << epList.size() << " points):";
        for (auto& ep : epList) cerr << " (" << ep.x << "," << ep.y << "," << ep.z << ")";
        cerr << "\n";
        int candCount = 0;
#endif

        for (const auto& ep : epList) {
            for (const auto& rot : rotations) {
                if (ep.x + rot.x > box.l ||
                    ep.y + rot.y > box.w ||
                    ep.z + rot.z > box.h) {
                    continue;
                }

                PlacedItem temp = {item.id, ep.x, ep.y, ep.z, rot.x, rot.y, rot.z};
                bool collide = false;
                for (const auto& alreadyPlaced : placedResults) {
                    if (isCollision(temp, alreadyPlaced)) {
                        collide = true;
                        break;
                    }
                }
                if (collide) continue;

#if DEBUG
                candCount++;
                cerr << "    Valid cand #" << candCount << ": EP(" << ep.x << "," << ep.y << "," << ep.z
                     << ") + rot(" << rot.x << "," << rot.y << "," << rot.z
                     << ") → placed at (" << ep.x << "," << ep.y << "," << ep.z
                     << ") size (" << rot.x << "," << rot.y << "," << rot.z << ")"
                     << "   SCORE(137): z=" << ep.z << " y=" << ep.y << " x=" << ep.x;
                if (ep.z < bestZ || (ep.z == bestZ && ep.y < bestY) || (ep.z == bestZ && ep.y == bestY && ep.x < bestX))
                    cerr << " ← BETTER!";
                cerr << "\n";
#endif

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

        if (!isPlaced) {
#if DEBUG
            cerr << "  ❌ FAILED to place item id=" << item.id << "\n";
#endif
            return false;
        }

        PlacedItem finalPlacement = {item.id, bestEP.x, bestEP.y, bestEP.z, bestSize.x, bestSize.y, bestSize.z};
        placedResults.push_back(finalPlacement);

#if DEBUG
        cerr << "  ✅ CHOSEN: placed at (" << bestEP.x << "," << bestEP.y << "," << bestEP.z
             << ") size (" << bestSize.x << "," << bestSize.y << "," << bestSize.z << ")\n";
        cerr << "     Reason: Z=" << bestZ << " Y=" << bestY << " X=" << bestX << " (Z→Y→X minimal)\n";
        cerr << "     Item bounds: x=[" << bestEP.x << "," << bestEP.x+bestSize.x
             << ") y=[" << bestEP.y << "," << bestEP.y+bestSize.y
             << ") z=[" << bestEP.z << "," << bestEP.z+bestSize.z << ")\n";
#endif

        updateEPList(epList, finalPlacement, placedResults);

#if DEBUG
        cerr << "  EP list after update (" << epList.size() << " points):";
        for (auto& ep : epList) cerr << " (" << ep.x << "," << ep.y << "," << ep.z << ")";
        cerr << "\n";
#endif
    }
    return true;
}

void updateEPList(vector<Point3D>& epList, const PlacedItem& newItem, const vector<PlacedItem>& placedResults) {
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

    validEPs.erase(unique(validEPs.begin(), validEPs.end(), [](const Point3D& a, const Point3D& b) {
        return a.x == b.x && a.y == b.y && a.z == b.z;
    }), validEPs.end());

    epList = validEPs;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int m, n;
    if (!(cin >> m >> n)) return 0;

    vector<Box> boxes(m);
    for (int i = 0; i < m; ++i) {
        boxes[i].id = i + 1;
        cin >> boxes[i].l >> boxes[i].w >> boxes[i].h;
        boxes[i].vol = boxes[i].l * boxes[i].w * boxes[i].h;
    }

    vector<Item> items(n);
    for (int i = 0; i < n; ++i) {
        items[i].id = i + 1;
        cin >> items[i].l >> items[i].w >> items[i].h >> items[i].allowRotate;
        items[i].vol = items[i].l * items[i].w * items[i].h;
    }

    sort(boxes.begin(), boxes.end(), [](const Box& a, const Box& b) {
        return a.vol < b.vol;
    });

    bool foundSolution = false;
    int chosenBoxId = -1;
    vector<PlacedItem> finalPlan;

    for (const auto& box : boxes) {
        vector<PlacedItem> currentPlan;
        if (packBox(box, items, currentPlan)) {
            foundSolution = true;
            chosenBoxId = box.id;
            finalPlan = currentPlan;
            break;
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
