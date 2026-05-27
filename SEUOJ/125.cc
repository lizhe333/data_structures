//图着色贪心算法
//固定颜色从1号扫描到n号

#include <iostream>
#include <vector>
using namespace std;

int soulution(vector<vector<int>>&adj,int nums){
    //用邻接表表示边的联通关系
    vector<int> color(nums+1,0);//记录点是否被涂色
    int colored_count=0;//记录已经被涂色的点的个数，用于终止循环
    int curr_color=0;//当前使用的颜色
    while(colored_count<nums){ 
    curr_color++;
    //以颜色为驱动，遍历所有点
    for(int i=1;i<=nums;i++){
        if(color[i]==0){
            //如果当前点还没有着色
            //检查他相邻的点是否被着了同一个颜色
            bool can_color=true;
            for(int neighbor:adj[i]){
                if(color[neighbor]==curr_color){
                    //如果有相邻的点被涂了，就不能涂色
                    can_color=false;
                    break;
                }
            }
            if(can_color){
                //如果当前点没有相邻的点被涂了，就可以涂色
                color[i]=curr_color;
                colored_count++;
            }
        }
    }
}
return curr_color;
   
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    if (!(cin >> n >> m)) return 0;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v); 
        adj[v].push_back(u); 
    }
    int total_colors = soulution(adj,n);
    cout << total_colors << "\n";
    return 0;
}