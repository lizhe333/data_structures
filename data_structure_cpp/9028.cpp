#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

vector<int> getToplogyOrder(int n,vector<int>& inDegree, vector<vector<int>>& graph){
    //需要入度数组和邻接表
    int len = n;
    //创建结果数组
    vector<int> res;
    //创建工作队列
    queue<int> q;
    //首先找到入度为0的点入队列
    for(int i = 1; i <= len; i++){
        if(inDegree[i] == 0){
            q.push(i);
            res.push_back(i);
        }
    }
    //开始排序
    while(!q.empty()){
        //首先出队列
        int curr = q.front();
        q.pop();
        //查找当前点所连接的点，然后更新入度
        for(int i= 0;i<graph[curr].size();i++){
            int next = graph[curr][i];
            inDegree[next]--;
            if(inDegree[next] == 0){
                q.push(next);
                res.push_back(next);
            }
        }

    }
    if(res.size() != len){
        return vector<int>();
    }

    else{
        return res;
    }

}
int main() {
    // 优化输入输出速度，防止超时
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    if (cin >> t) {
        while (t--) {
            int n, m;
            cin >> n >> m;

      
            vector<vector<int>> graph(n + 1);
            vector<int> inDegree(n + 1, 0);

           
            for (int i = 0; i < m; i++) {
                int u, v;
                cin >> u >> v;
                // u -> v (Y必须出现在X之后)
                graph[u].push_back(v);
                inDegree[v]++;
            }

            vector<int> result = getToplogyOrder(n, inDegree, graph);

        
            if (result.empty()) {
                cout << "0" << endl;
            } else {
                for (int i = 0; i < result.size(); i++) {
                    cout << result[i] << (i == result.size() - 1 ? "" : " ");
                }
                cout << endl;
            }
        }
    }
    return 0;
}