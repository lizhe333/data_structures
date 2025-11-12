//假设 $T$ 是一棵以 $v$ 为根的树。 $T$ 的边是无向的。 
//$T$ 中的每条边都有一个非负的长度。请编写一个 C++ 函数，用来确定从根 $v$ 到 $T$ 中其余顶点的最短路径长度。
//树的遍历不需要用标准的迪杰斯特拉算法。
#include <iostream>
#include <vector>
#include <utility> // 用于 std::pair
#include <limits>  // 用于 std::numeric_limits
using namespace std;
//定义邻居节点
using Neighbour=pair<int, int>;// <Node,weight>
using adjlist = vector<vector<Neighbour>>;//定义邻接表
class Solution{
    public:
    //先写一个遍历的辅助函数
    //参数：起始节点，父节点，邻接表，距离数组
    void dfs(int s,int f,adjlist& adj,vector<int>& dist){
        //遍历开始节点的所以相邻节点
        for (auto& neighbour : adj[s]){
            int point = neighbour.first;
            int weight = neighbour.second;
            //如果是刚刚的父节点就跳过
        if(point==f)
            continue;
        dist[point] = dist[s] + weight;
             dfs(point,s,adj,dist);
        }
    };

    vector<int>solution(int v,adjlist& adj){
        //初始话一个距离数组
        vector<int>dist(adj.size(),numeric_limits<int>::max());
        dist[v] = 0;
        //根节点没有父节点，拿-1来占位
        dfs(v,-1,adj,dist);
        return dist;
    };
};