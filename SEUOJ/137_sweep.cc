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

vector<Point3D> getValidRotations(const Item& it) {
    vector<Point3D> r;
    r.push_back({it.l, it.w, it.h});
    if (it.l != it.w) r.push_back({it.w, it.l, it.h});
    if (it.allowRotate == 1) {
        r.push_back({it.w, it.h, it.l});
        r.push_back({it.h, it.w, it.l});
        r.push_back({it.l, it.h, it.w});
        r.push_back({it.h, it.l, it.w});
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
    for (const auto& it : placed)
        if (pt.x >= it.px && pt.x < it.px + it.sl &&
            pt.y >= it.py && pt.y < it.py + it.sw &&
            pt.z >= it.pz && pt.z < it.pz + it.sh) return true;
    return false;
}
void updateEPList(vector<Point3D>& ep, const PlacedItem& it, const vector<PlacedItem>& placed) {
    ep.push_back({it.px + it.sl, it.py, it.pz});
    ep.push_back({it.px, it.py + it.sw, it.pz});
    ep.push_back({it.px, it.py, it.pz + it.sh});
    vector<Point3D> v;
    for (const auto& e : ep) if (!isPointInsideAnyItem(e, placed)) v.push_back(e);
    sort(v.begin(), v.end(), [](const Point3D& a, const Point3D& b){
        if (a.z != b.z) return a.z < b.z;
        if (a.y != b.y) return a.y < b.y;
        return a.x < b.x; });
    v.erase(unique(v.begin(), v.end(), [](const Point3D& a, const Point3D& b){
        return a.x==b.x && a.y==b.y && a.z==b.z; }), v.end());
    ep = v;
}
bool packBox(const Box& box, const vector<Item>& items, vector<PlacedItem>& out) {
    vector<Point3D> ep{{0,0,0}};
    out.clear();
    for (const auto& item : items) {
        bool placed = false;
        Point3D bEP{-1,-1,-1}, bSz{-1,-1,-1};
        long long bz=1e18, by=1e18, bx=1e18;
        vector<Point3D> rots = getValidRotations(item);
        for (const auto& e : ep) for (const auto& r : rots) {
            if (e.x+r.x>box.l || e.y+r.y>box.w || e.z+r.z>box.h) continue;
            PlacedItem t{item.id, e.x,e.y,e.z, r.x,r.y,r.z};
            bool col=false;
            for (const auto& q : out) if (isCollision(t,q)){col=true;break;}
            if (col) continue;
            if (e.z<bz || (e.z==bz && e.y<by) || (e.z==bz && e.y==by && e.x<bx)) {
                bz=e.z; by=e.y; bx=e.x; bEP=e; bSz=r; placed=true;
            }
        }
        if (!placed) return false;
        PlacedItem fp{item.id, bEP.x,bEP.y,bEP.z, bSz.x,bSz.y,bSz.z};
        out.push_back(fp);
        updateEPList(ep, fp, out);
    }
    return true;
}
bool cmpVolume(const Item& a, const Item& b){ return a.vol > b.vol; }
bool cmpBaseArea(const Item& a, const Item& b){ return a.l*a.w > b.l*b.w; }
bool cmpHeight(const Item& a, const Item& b){ return a.h > b.h; }
bool cmpLongestSide(const Item& a, const Item& b){ return max({a.l,a.w,a.h}) > max({b.l,b.w,b.h}); }

int main(int argc, char** argv) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // args: TIME_LIMIT_MS  PER_BOX_RESTART_CAP
    double TIME_LIMIT = (argc>1 ? atof(argv[1]) : 15.0) / 1000.0;
    int RESTART_CAP   = (argc>2 ? atoi(argv[2]) : 200);

    int m, n;
    if (!(cin >> m >> n)) return 0;
    vector<Box> boxes(m);
    for (int i=0;i<m;++i){ boxes[i].id=i+1; cin>>boxes[i].l>>boxes[i].w>>boxes[i].h; boxes[i].vol=boxes[i].l*boxes[i].w*boxes[i].h; }
    vector<Item> items(n);
    long long totalVol=0;
    for (int i=0;i<n;++i){ items[i].id=i+1; cin>>items[i].l>>items[i].w>>items[i].h>>items[i].allowRotate; items[i].vol=items[i].l*items[i].w*items[i].h; totalVol+=items[i].vol; }
    sort(boxes.begin(),boxes.end(),[](const Box&a,const Box&b){return a.vol<b.vol;});

    auto t0 = chrono::steady_clock::now();
    auto elapsed=[&]{ return chrono::duration<double>(chrono::steady_clock::now()-t0).count(); };

    vector<function<bool(const Item&,const Item&)>> strats = { cmpVolume, cmpBaseArea, cmpHeight, cmpLongestSide };
    mt19937 rng(42);

    int chosen=-1; vector<PlacedItem> plan;
    for (int i=0;i<m && chosen==-1;++i){
        if (totalVol > boxes[i].vol) continue;
        for (auto& s : strats){
            vector<Item> tmp=items; sort(tmp.begin(),tmp.end(),s);
            vector<PlacedItem> p;
            if (packBox(boxes[i],tmp,p)){ chosen=i; plan=p; break; }
        }
        if (chosen!=-1) break;
        vector<Item> sh=items;
        for (int k=0;k<RESTART_CAP;++k){
            if (elapsed()>=TIME_LIMIT) break;
            shuffle(sh.begin(),sh.end(),rng);
            vector<PlacedItem> p;
            if (packBox(boxes[i],sh,p)){ chosen=i; plan=p; break; }
        }
    }
    if (chosen==-1){ cout<<"DORAYAKI\n"; return 0; }
    cout<<boxes[chosen].id<<"\n";
    sort(plan.begin(),plan.end(),[](const PlacedItem&a,const PlacedItem&b){return a.id<b.id;});
    for (auto& p : plan)
        cout<<p.px<<" "<<p.py<<" "<<p.pz<<" "<<p.sl<<" "<<p.sw<<" "<<p.sh<<"\n";
    return 0;
}
