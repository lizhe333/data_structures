#include<iostream>
#include<vector>
using namespace std;
//初始化
int parent[10001];

int find(int x){
    if(x==parent[x])
        return x;
    else{
        // 递归找老大，顺手把沿途所有人的 parent 直接指向最高老大（路径压缩）
        parent[x]=find(parent[x]);
        return parent[x];
    }   
}
bool unite(int x,int y){
//两个待合并的节点x,y
int rootX  = find(x);
int rootY  = find(y);
if(rootX==rootY)
    return false;
else{
    parent[rootX]=rootY;
    return true;
}
}
void solve() {
    int n, m;
    if (!(cin >> n >> m)) return;


    for (int i = 1; i <= n; i++) {
        parent[i] = i;
    }


    int count = n;

    // 2. 读取边并合并
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        
        // 尝试合并 u 和 v
        if (unite(u, v)) {
     
            count--;
        }
    }

 
    cout << count << endl;
}

int main() {
    // IO 加速
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    if (cin >> T) {
        while (T--) {
            solve();
        }
    }
    return 0;
}
