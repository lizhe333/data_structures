//树上着色问题求解

#include <iostream>
#include<vector>
using namespace std;

const int Max=50005;
//用邻接表存储树
vector<int> G[Max];
//动态规划数组
int dp[Max][2];

//树形DP求解
void dfs(int u,int parent){
    dp[u][0]=0; //u不选择
    dp[u][1]=1; //u选择
    for(int v:G[u]){
        if(v==parent) continue;
        dfs(v,u);
        dp[u][0]+=max(dp[v][0],dp[v][1]); //u不选择，v可以选择或不选择
        dp[u][1]+=dp[v][0]; //u选择，v不能选择
    }
}

void solve(){
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        G[i].clear();
    }
    // 读取 N-1 条边，构建无向树
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    // 如果只有一个节点，直接输出 1
    if (n == 1) {
        cout << 1 << "\n";
        return;
    }
    // 以 1 号节点作为根节点开始 DFS
    dfs(1, 0);
    // 最终答案是根节点染白和染黑两种情况下的最大值
    cout << max(dp[1][0], dp[1][1]) << "\n";
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}