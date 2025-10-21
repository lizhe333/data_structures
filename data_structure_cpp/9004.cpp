////用BFS算法来找最短路径
//#include<iostream>
//#include<queue>
//#include<cstring>
//#include<vector>
//#include<string>
//using namespace std;
//void slove() {
//	int n, m;
//	cin >> n >> m;
//	vector<string>grid(n);
//	int start_r = -1, start_c = -1;
//	int goal_r = -1, goal_c = -1;
//	for (int i = 0; i < n; ++i) {
//		cin >> grid[i];
//		for (int j = 0; j < m; ++j) {
//			if (grid[i][j] == 'S') {
//				start_r = i;
//				start_c = j;
//			}
//			else if (grid[i][j] == 'G') {
//				goal_r = i;
//				goal_c = j;
//			}
//		}
//	}
//	//准备数据结构
//
//	queue<pair<int, int>>q;
//	vector<vector<int>>visited(n,vector<int>(m,-1));
//	//下面创建visited的用法是
//	//先在内存中创建一个模板行vector<bool>(m,false)
//	//然后创建外部向量,visited,他的大小是n,
//	//然后把n个拷贝的模板行vector<bool>(m,false)都塞进去
//
//	//定义四个方向
//	int dr[] = { -1,1,0,0 };
//	int dc[] = { 0,0,-1,1 };
//
//	q.push(make_pair(start_r, start_c));
//	visited[start_r][start_c] = 0;
//	while (!q.empty()) {
//		//去出队首元素
//		pair<int, int>cur = q.front();
//		q.pop();
//		int r = cur.first;
//		int c = cur.second;
//		int current_step = visited[r][c];
//		if (r == goal_r && c == goal_c) {
//			break;
//		}
//		//探索四个方向
//		for (int i = 0; i < 4; ++i) {
//			pair<int, int>next = make_pair(r + dr[i], c + dc[i]);
//			if (next.first >= 0 && next.first < n && next.second >= 0 && next.second < m) {
//				if (grid[next.first][next.second] != '#' && visited[next.first][next.second]==-1) {
//					q.push(next);
//					visited[next.first][next.second] = current_step+1;
//				}
//			}
//		}
//
//	}
//	//得出最后的结论
//	cout << visited[goal_r][goal_c] << endl;
//};
//int main() {
//	// 提高C++的IO效率
//	ios_base::sync_with_stdio(false);
//	cin.tie(NULL);
//	cout.tie(NULL);
//
//	int T;
//	cin >> T;
//	while (T--) {
//		slove();
//	}
//	return 0;
//}
