//最大独立集问题
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int max_count=0;
void dfs(vector<vector<int>>& graph,int current_count,int u,vector<bool>& visited,int n){
    //剪枝
    if(current_count+n-u+1<=max_count){
        return ;
    }
    if(u==n){
        max_count=max(max_count,current_count);
        return;
    }
    //回头检查u的选择是否合法
    bool conflict=false;
    for(int i=0;i<graph[u].size();i++){
        if(visited[i]&&graph[u][i]==1){
            conflict=true;
            break;
        }
    }
    if(!conflict){
        //如果没有冲突
        //可以访问u
        visited[u]=true;
        dfs(graph,current_count+1,u+1,visited,n);
        visited[u]=false;
    }
    //有冲突，正常往后遍历
    dfs(graph,current_count,u+1,visited,n);

}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    // 读取顶点数和边数
    if (!(cin >> n >> m)) return 0;
    vector<vector<int>> graph(n, vector<int>(n, 0));
    // 初始化标记数组
    vector<bool> visited(n, false);

    // 读取 m 条边
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        u--; 
        v--;
        
        // 无向图，双向标记
        graph[u][v] = 1;
        graph[v][u] = 1;
    }
    dfs(graph, 0, 0, visited, n);
    cout << max_count << "\n";
    return 0;
}