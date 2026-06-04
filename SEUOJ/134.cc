//回溯旅行商问题
#include<iostream>
#include<vector>
using namespace std;
const int INF = 1e9; 
int n;
vector<vector<int>> dist; // 距离矩阵
vector<bool> visited;    
int best_cost = INF;
void backtrace(int curr_city,int curr_cost,int step){
    //剪枝
    if(curr_cost>=best_cost){
        return; 
    }
    if(step==n){
        best_cost=min(best_cost,curr_cost+dist[curr_city][1]);
        return ;
    }

    //开始遍历所有城市，尝试从当前城市到其他城市
    for(int i=1;i<=n;i++){
        if(!visited[i]){
            //尝试访问城市i
            visited[i]=true;
            backtrace(i,curr_cost+dist[curr_city][i],step+1);
            visited[i]=false;//回溯就撤销访问标记
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    if (!(cin >> n)) return 0;
    dist.assign(n + 1, vector<int>(n + 1, 0));
    visited.assign(n + 1, false);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> dist[i][j];
        }
    }

    visited[1] = true; 
    backtrace(1, 0, 1); 
    cout << best_cost << "\n";
    return 0;
}