#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <functional>
#include <cstdlib>
using namespace std;

struct Point3D { long long x, y, z; };
struct Box  { int id; long long l, w, h, vol; };
struct Item { int id; long long l, w, h; int allowRotate; long long vol; };
struct PlacedItem { int id; long long px, py, pz, sl, sw, sh; };

vector<Point3D> getValidRotations(const Item& item) {
    vector<Point3D> r;
    r.push_back({item.l, item.w, item.h});
    if (item.l != item.w) r.push_back({item.w, item.l, item.h});
    if (item.allowRotate == 1) {
        r.push_back({item.w, item.h, item.l});
        r.push_back({item.h, item.w, item.l});
        r.push_back({item.l, item.h, item.w});
        r.push_back({item.h, item.l, item.w});
    }
    return r;
}

bool isCollision(const PlacedItem& a, const PlacedItem& b) {
    bool dx = (a.px + a.sl <= b.px) || (b.px + b.sl <= a.px);
    bool dy = (a.py + a.sw <= b.py) || (b.py + b.sw <= a.py);
    bool dz = (a.pz + a.sh <= b.pz) || (b.pz + b.sh <= a.pz);
    return !dx && !dy && !dz;
}

bool isPointInsideAnyItem(const Point3D& pt, const vector<PlacedItem>& placed) {
    for (const auto& it : placed) {
        if (pt.x >= it.px && pt.x < it.px + it.sl &&
            pt.y >= it.py && pt.y < it.py + it.sw &&
            pt.z >= it.pz && pt.z < it.pz + it.sh)
            return true;
    }
    return false;
}

static inline long long ov(long long a0, long long a1, long long b0, long long b1) {
    return min(a1, b1) - max(a0, b0);
}


long long contactScore(const PlacedItem& t, const vector<PlacedItem>& placed, const Box& box) {
    long long s = 0;
    // 与容器六个面的接触
    if (t.pz == 0)              s += t.sl * t.sw;          // 底
    if (t.pz + t.sh == box.h)   s += t.sl * t.sw;          // 顶
    if (t.py == 0)              s += t.sl * t.sh;          // 后
    if (t.py + t.sw == box.w)   s += t.sl * t.sh;          // 前
    if (t.px == 0)              s += t.sw * t.sh;          // 左
    if (t.px + t.sl == box.l)   s += t.sw * t.sh;          // 右
    // 与已放置物体的贴合面积
    for (const auto& p : placed) {
        long long oy = ov(t.py, t.py + t.sw, p.py, p.py + p.sw);
        long long oz = ov(t.pz, t.pz + t.sh, p.pz, p.pz + p.sh);
        long long ox = ov(t.px, t.px + t.sl, p.px, p.px + p.sl);
        // X 方向贴面（左右相邻）
        if (oy > 0 && oz > 0 &&
            (t.px == p.px + p.sl || p.px == t.px + t.sl)) s += oy * oz;
        // Y 方向贴面（前后相邻）
        if (ox > 0 && oz > 0 &&
            (t.py == p.py + p.sw || p.py == t.py + t.sw)) s += ox * oz;
        // Z 方向贴面（上下相邻）
        if (ox > 0 && oy > 0 &&
            (t.pz == p.pz + p.sh || p.pz == t.pz + t.sh)) s += ox * oy;
    }
    return s;
}

long long dropZ(const PlacedItem& t, const vector<PlacedItem>& placed) {
    long long z = 0;
    for (const auto& p : placed) {
        long long ox = ov(t.px, t.px + t.sl, p.px, p.px + p.sl);
        long long oy = ov(t.py, t.py + t.sw, p.py, p.py + p.sw);
        if (ox > 0 && oy > 0) z = max(z, p.pz + p.sh); 
    }
    return z;
}

void updateEPList(vector<Point3D>& epList, const PlacedItem& it,
                  const vector<PlacedItem>& placed) {
    epList.push_back({it.px + it.sl, it.py, it.pz});
    epList.push_back({it.px, it.py + it.sw, it.pz});
    epList.push_back({it.px, it.py, it.pz + it.sh});

    vector<Point3D> v;
    for (const auto& ep : epList)
        if (!isPointInsideAnyItem(ep, placed)) v.push_back(ep);

    sort(v.begin(), v.end(), [](const Point3D& a, const Point3D& b) {
        if (a.z != b.z) return a.z < b.z;
        if (a.y != b.y) return a.y < b.y;
        return a.x < b.x;
    });
    v.erase(unique(v.begin(), v.end(), [](const Point3D& a, const Point3D& b) {
        return a.x == b.x && a.y == b.y && a.z == b.z;
    }), v.end());
    epList = v;
}

bool packBox(const Box& box, const vector<Item>& items, vector<PlacedItem>& out) {
    vector<Point3D> epList{{0, 0, 0}};
    out.clear();

    for (const auto& item : items) {
        bool placed = false;
        PlacedItem best{};
        long long bestScore = -1;
        long long bz = 0, by = 0, bx = 0;

        vector<Point3D> rots = getValidRotations(item);
        for (const auto& ep : epList) {
            for (const auto& rot : rots) {
               
                PlacedItem t{item.id, ep.x, ep.y, ep.z, rot.x, rot.y, rot.z};
                t.pz = dropZ(t, out);

                if (t.px + t.sl > box.l || t.py + t.sw > box.w || t.pz + t.sh > box.h)
                    continue;

                bool collide = false;
                for (const auto& q : out)
                    if (isCollision(t, q)) { collide = true; break; }
                if (collide) continue;

                long long sc = contactScore(t, out, box);
         
                if (sc > bestScore ||
                    (sc == bestScore && (t.pz < bz ||
                    (t.pz == bz && t.py < by) ||
                    (t.pz == bz && t.py == by && t.px < bx)))) {
                    bestScore = sc; best = t;
                    bz = t.pz; by = t.py; bx = t.px;
                    placed = true;
                }
            }
        }
        if (!placed) return false;
        out.push_back(best);
        updateEPList(epList, best, out);
    }
    return true;
}

bool cmpVolume(const Item& a, const Item& b)     { return a.vol > b.vol; }
bool cmpBaseArea(const Item& a, const Item& b)   { return a.l * a.w > b.l * b.w; }
bool cmpHeight(const Item& a, const Item& b)     { return a.h > b.h; }
bool cmpLongestSide(const Item& a, const Item& b){
    return max({a.l, a.w, a.h}) > max({b.l, b.w, b.h});
}
bool cmpMaxDim(const Item& a, const Item& b) {
    long long ma = max({a.l,a.w,a.h}), mb = max({b.l,b.w,b.h});
    if (ma != mb) return ma > mb;
    return a.vol > b.vol;
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
    long long totalVol = 0;
    for (int i = 0; i < n; ++i) {
        items[i].id = i + 1;
        cin >> items[i].l >> items[i].w >> items[i].h >> items[i].allowRotate;
        items[i].vol = items[i].l * items[i].w * items[i].h;
        totalVol += items[i].vol;
    }

    sort(boxes.begin(), boxes.end(),
         [](const Box& a, const Box& b) { return a.vol < b.vol; });

    auto t0 = chrono::steady_clock::now();
    const double TIME_LIMIT = 0.018;

    vector<function<bool(const Item&, const Item&)>> strategies = {
        cmpVolume, cmpBaseArea, cmpLongestSide, cmpMaxDim, cmpHeight
    };
    mt19937 rng(12345);
    const int RESTART_CAP = 100000;

    int chosen = -1;
    vector<PlacedItem> plan;
    double bestScore = -1;

    for (int i = 0; i < m; ++i) {
        if (totalVol > boxes[i].vol) continue;

        vector<PlacedItem> currentPlan;
        bool found = false;

        for (auto& strat : strategies) {
            vector<Item> tmp = items;
            sort(tmp.begin(), tmp.end(), strat);
            vector<PlacedItem> p;
            if (packBox(boxes[i], tmp, p)) { currentPlan = p; found = true; break; }
        }
        if (!found) {
            vector<Item> sh = items;
            for (int k = 0; k < RESTART_CAP; ++k) {
                double el = chrono::duration<double>(chrono::steady_clock::now() - t0).count();
                if (el >= TIME_LIMIT) break;
                shuffle(sh.begin(), sh.end(), rng);
                vector<PlacedItem> p;
                if (packBox(boxes[i], sh, p)) { currentPlan = p; found = true; break; }
            }
        }

        if (found) {
            double el = chrono::duration<double>(chrono::steady_clock::now() - t0).count();
            double Tc = max(20.0, el * 1000);
            double St = min(200.0, 100.0 * sqrt(Tc / 20.0));
            double Sq = 100.0 * totalVol / boxes[i].vol;
            double score = 0.65 * Sq + 0.35 * St;

            if (score > bestScore) {
                bestScore = score;
                chosen = i;
                plan = currentPlan;
            }
        }
    }

    double internalMs = chrono::duration<double, milli>(chrono::steady_clock::now() - t0).count();
    if (getenv("PACK_DEBUG")) fprintf(stderr, "internal=%.1fms\n", internalMs);

    if (chosen == -1) { cout << "DORAYAKI\n"; return 0; }

    cout << boxes[chosen].id << "\n";
    sort(plan.begin(), plan.end(),
         [](const PlacedItem& a, const PlacedItem& b) { return a.id < b.id; });
    for (const auto& p : plan)
        cout << p.px << " " << p.py << " " << p.pz << " "
             << p.sl << " " << p.sw << " " << p.sh << "\n";
    return 0;
}
