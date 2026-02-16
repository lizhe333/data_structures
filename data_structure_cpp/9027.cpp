#include<iostream>
#include<algorithm>
#include<vector>

const int MAX = 10005;
using namespace std;
//创建dp数组，存储权重的数组，以及一个邻接表来存储图
long long  dp[MAX][2];
int value[MAX];
vector<int> adj[MAX];

//递归函数

void dfs(int curr,int parent){
    //先是初始化这个节点
    dp[curr][0] = 0;
    dp[curr][1] = value[curr];
    //遍历curr的每一个邻居
    for(int i:adj[curr]){
        //首先是不能走回头路
        if(i == parent)
            continue;

        //先处理子节点
        dfs(i,curr);
        dp[curr][0] +=max(dp[i][0],dp[i][1]);
        dp[curr][1] +=dp[i][0];

    }
    //这个递归的终止条件是隐含在for循环当中，没有了adj里面的邻居以后自然就跳出dfs了
    
}

void solve(){
    int n;
    if(!(cin>>n))return;

    //清空邻接表
    for(int i=1;i<=n;i++){

        adj[i].clear();
    }
    for(int i=1;i<=n;i++){

        cin>>value[i];
    }
    //读取n-1条边，构建树
    for(int i=1;i<n;i++){
        int a,b;
        cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1,0);
    cout<<max(dp[1][0],dp[1][1])<<endl;

}int main() {

    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t; // 读取测试组数 T
    while (t--) {
        solve(); // 循环处理每一组
    }
    return 0;
}
