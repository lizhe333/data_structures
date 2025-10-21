////使用DFS算法来寻找
////一般是使用递归来实现
////首先要准备一个布尔数组来记录是否访问过（visit）
//#include<iostream>
//#include<vector>
//#include<string>
//
//using namespace std;
//int n, m;
//vector<string>graph;
//vector<vector<bool>>visit;
//
////定义四个方向
//int dr[] = { -1,1,0,0 };
//int dc[] = { 0,0,-1,1 };
//
////写DFS递归函数
//void dfs(int r, int c) {
//	if (r < 0 || r >= n || c < 0 || c >= m || visit[r][c] || graph[r][c] == '#') {
//		//如果点不合法，或者是走过了，则回溯
//		return;
//	}
//	visit[r][c] = true;
//	for (int i = 0; i < 4; i++) {
//		int nr = r + dr[i];
//		int nc = c + dc[i];
//		dfs(nr, nc);
//	}
//}
//
//void solve() {
//	cin >> n >> m;
//	graph.assign(n, ""); // 重置 grid
//	visit.assign(n, vector<bool>(m, false)); // 重置 visited
//
//	int start_r = -1, start_c = -1;
//	int goal_r = -1, goal_c = -1;
//
//	for (int i = 0; i < n; ++i) {
//		cin >> graph[i];
//		for (int j = 0; j < m; ++j) {
//			if (graph[i][j] == 'S') {
//				start_r = i;
//				start_c = j;
//			}
//			else if (graph[i][j] == 'G') {
//				goal_r = i;
//				goal_c = j;
//			}
//		}
//	}
//
//	// 2. 从起点开始 DFS
//	dfs(start_r, start_c);
//
//	// 4. 得出结论
//	if (visit[goal_r][goal_c]) {
//		cout << "exist!" << endl;
//	}
//	else {
//		cout << "not exist!" << endl;
//	}
//}
//int main() {
//	ios_base::sync_with_stdio(false);
//	cin.tie(NULL);
//	cout.tie(NULL);
//
//	int T;
//	cin >> T;
//	while (T--) {
//		solve();
//	}
//	return 0;
//}