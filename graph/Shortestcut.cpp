
#include<iostream>
#include<vector>
#include <algorithm>
#include <queue>
using namespace std;
//--------------------------Dijkstra算法实现----------------------------------
//该算法返回的是起点距离所有点的最短距离
class Dijkstra {
public:
	vector<int>dijkstra(vector<vector<pair<int, int>>>& adj, int start, int n) {

		//初始化数组
		vector<int>min_dist(n, INT_MAX);
		vector<bool>visited(n, false);
		min_dist[start] = 0;
		//声明一个最小堆
		priority_queue < pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>qs;
		qs.push(make_pair(0, start));

		//开始主循环
		while (!qs.empty()) {
			//取出堆顶元素
			int d = qs.top().first;
			int v = qs.top().second;

			if (visited[v]) {
				continue;
			}
			//加入访问数组
			visited[v] = true;

			//更新其他边
			for (auto& edge : adj[v]) {
			int u = edge.first;
			int w = edge.second;
			if (visited[u] == false && min_dist[u] > d + w){
			//更新距离
                min_dist[u] = d + w;
				qs.push(make_pair(min_dist[u], u));
			}
			}
		}
		return min_dist;
	};
};

//--------------------------Floyd算法实现----------------------------------
class Floyd {
public:
	vector<vector<int>>floyd(vector<vector<int>>& graph, int n) {
		vector<vector<int>>min_dist(n, vector<int>(n, INT_MAX));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				min_dist[i][j] = graph[i][j];
			}
		}
		for (int k = 0; k < n; k++) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (min_dist[i][k] + min_dist[k][j] < min_dist[i][j])
						min_dist[i][j] = min_dist[i][k] + min_dist[k][j];
				}
			}
		}
	}
};