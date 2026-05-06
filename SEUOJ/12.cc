#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

struct Point {
    double x, y;
  
};

//按照x排序
bool compareX(const Point& a, const Point& b) {
    return a.x < b.x;
}

//计算距离
double distance(const Point& a, const Point& b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

//temp数组用来进行归并排序
Point temp[50005],p[50005];

double solve(int l,int r){
    if(l>=r) return 1e18;
    if(l+1==r){
        //此时按照两个点的y值进行排序
        if(p[l].y>p[r].y) swap(p[l],p[r]);
        return distance(p[l],p[r]);
    }

    int mid=(l+r)>>1;
    int mid_x=p[mid].x;//记录中线的x坐标
    double d=min(solve(l,mid),solve(mid+1,r));

    //归并排序y的坐标，合并已经排好序的
    int i=l,j=mid+1,k=l;
    while(i<=mid && j<=r){
        if(p[i].y<p[j].y) temp[k++]=p[i++];
        else temp[k++]=p[j++];
    }
    while(i<=mid){
        temp[k++]=p[i++];
    }
    while(j<=r){
        temp[k++]=p[j++];
    }
    for(int i=l;i<=r;i++) p[i]=temp[i]; 
    //筛选长方形区域
    vector<int> v;
    for(int i=l;i<=r;i++){
        if(abs(p[i].x-mid_x)<d) v.push_back(i);
    }
    for (i = 0; i < v.size(); i++) {
        for (j = i + 1; j < v.size() && (p[v[j]].y - p[v[i]].y) < d; j++) {
            d = min(d, distance(p[v[i]], p[v[j]]));
        }
    }
    return d;
}
int main() {
    int M;
    if (!(cin >> M)) return 0;
    while (M--) {
        int N;
        cin >> N;
        for (int i = 0; i < N; i++) cin >> p[i].x >> p[i].y;
        sort(p, p + N, compareX);
        cout << fixed << setprecision(2) << solve(0, N - 1) << endl;
    }
    return 0;
}
