#include<iostream>
#include<vector>
#include<algorithm>
#include<numeric>

struct Edge {
    int u, v;
    int weight;
    //重载<,来让sort函数可以排序
    bool operator<(const Edge& e) const {
        return weight < e.weight;
	}
};

//定义父节点
//定义并查集的数据
//parent[i]表示i的父节点s
std::vector<int> parent;

//并查集的find操作
//使用路径压缩优化
int find(int i) {
    if (parent[i] == i) {
    return i;
    }
    return parent[i] = find(parent[i]);
}

//并查集的合并操作
bool unite(int i, int j) {
  int root_i = find(i);
  int root_j = find(j);

  if (root_i != root_j) {
    //将一个根连接到另一个根上
      parent[root_i] = root_j;
      return true;
  }
  return false;
}
long long  Kruskal(int n,std::vector<Edge>& edges) {
    //首先将边按照权重排序
    std::sort(edges.begin(), edges.end());

    //初始化并查集
    //需要n+1个空间，顶点是从1~n
    parent.resize(n + 1);
    //初始化的时候每个节点都是自己的父节点
    for (int i = 0; i <= n; ++i) {
		parent[i] = i;
    }
    long long total_weight = 0;
    int edge_count = 0;

    for (const auto& edge : edges) {
        if (find(edge.u) != find(edge.v)) {
        //如果这两条边是不联通的
            unite(edge.u, edge.v);
            total_weight += edge.weight;
            edge_count++;
        }
        if (edge_count == n - 1) {
            break;
        }
    
    }
    return total_weight;
    
}
int main() { 
    int T;
	std::cin >> T;
    while (T--) {
        int n, m;
        std::cin >> n >> m;

        // 存储所有 m 条边
        std::vector<Edge> edges(m);
        for (int i = 0; i < m; ++i) {
            std::cin >> edges[i].u >> edges[i].v >> edges[i].weight;
		}


        //开始kruskal算法
        long long mst_weight = Kruskal(n, edges);

        // 输出结果
        std::cout << mst_weight << std::endl;
      
    }
    return 0;
}