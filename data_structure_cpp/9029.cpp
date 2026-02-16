#include<iostream>
#include<vector>
#include<queue>
using namespace std;

vector<int> dijkstra(int strat,int end,const vector<vector<pair<int,int>>>adj){
    //声明一个标记数组
    vector<bool>visited(adj.size(),false);
    //声明一个最短距离数组，初始化所有值为正无穷
    vector<int>dist(adj.size(),INT_MAX);

    //创建一个最短距离优先队列，使用pair存储距离和节点编号
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>qs;
    //将起点入队列

    qs.push(make_pair(0,strat));
    dist[strat]=0;
    //开始循环
    while(!qs.empty()){
        //首先取出距离最小的点
        pair<int ,int >curr = qs.top();
        qs.pop();
        int w = curr.first;
        int u = curr.second;
        if(visited[u]){

            continue;
        }
        visited[u]=true;
        //更新距离
        for(auto &edge:adj[u]){
            int v = edge.first;
            int w = edge.second;
            if(dist[v]>dist[u]+w){
                //新的路更近
                dist[v ] = dist[u]+w;
                qs.push(make_pair(dist[v],v));
            }
        }
    }
    return dist;
}
int main() {
    // 【优化】关闭同步流，加快输入输出速度
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    if (cin >> T) {
        while (T--) {
            int n, E, s, t;
            cin >> n >> E >> s >> t;


            vector<vector<pair<int, int>>> adj(n + 1);

            for (int i = 0; i < E; i++) {
                int u, v, w;
                cin >> u >> v >> w;
              
                adj[u].push_back({v, w}); // u -> v
                adj[v].push_back({u, w}); // v -> u
            }

        
            vector<int> result = dijkstra(s, n, adj);

        
     
            if (result[t] == INT_MAX) {
                cout << "-1" << endl;
            } else {
                cout << result[t] << endl;
            }
        }
    }
    return 0;
}