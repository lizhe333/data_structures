#include<iostream>
#include<vector>
#include<list>
#include<stdexcept>
#include<string>

using namespace std;

//邻接矩阵
//优点：O(1)的复杂度来查找边
//缺点：空间复杂度O(V^2)
class MatrixGraph {
private:
	int numVertex;
	vector<vector<int>> matrix;
	bool isValid(int v, int w) {
		return (v >= 0 && v < numVertex) && (w >= 0 && w < numVertex);
	}
public:
	MatrixGraph(int numVertex) : numVertex(numVertex)
	{
		//最外面的n是创建数组，里面的n是创建数组的元素
		matrix.resize(numVertex, vector<int>(numVertex, 0));
	}

	//添加权重为weight的边,默认权重为1
	void addEdge(int v, int w, int weight = 1) {
		if (isValid(v, w)) {
			matrix[v][w] = weight;
		}
		else {
			throw invalid_argument("Invalid vertex");
		}
	}

	// 打印邻接矩阵
	void printGraph() {
		cout << "\t";
		for (int i = 0; i < numVertex; ++i) cout << i << "\t";
		cout << "\n--------------------------\n";
		for (int i = 0; i < numVertex; ++i) {
			cout << i << " |\t";
			for (int j = 0; j < numVertex; ++j) {
				if (matrix[i][j] == 0) {
					cout << "0\t";
				}
				else {
					cout << matrix[i][j] << "\t";
				}
			}
			cout << endl;
		}
	}
};
void matrix_main() {
	cout << "--- 1. 邻接矩阵 (Adjacency Matrix) ---" << endl;
	cout << "实现讲义中的有向图 G3 [cite: 25, 123]\n" << endl;
	MatrixGraph g(5);
	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(1, 2);
	g.addEdge(2, 3);
	g.addEdge(3, 4);
	g.printGraph();
};

//领接表
// 核心思想：一个包含 V 个链表的数组，第 i 个链表存储 i 的所有邻居 
// 优点：O(V+E) 空间，非常适合稀疏图 
class AdjListGraph {
private:
	int numVertex;
	vector<list<int>> adj;
public:
	AdjListGraph(int numVertex) : numVertex(numVertex)
	{
		adj.resize(numVertex);
	}
	void addEdge(int v, int w) {
		//由于是邻接表，所以两个都要添加
		adj[v].push_back(w);
		adj[w].push_back(v);
	}
	// 打印邻接表
	void printGraph() {
		for (int i = 0; i < numVertex; ++i) {
			cout << "[" << i << "] -> ";
			for (int v : adj[i]) {
				cout << v << " -> ";
			}
			cout << "null" << endl;
		}
	}
};
void adjlist_main() {
	cout << "\n--- 2. 邻接表 (Adjacency List) ---" << endl;
	cout << "实现讲义中的无向图 G1 [cite: 18, 20, 205]\n" << endl;
	AdjListGraph g(5);
	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(1, 2);
	g.addEdge(2, 3);
	g.addEdge(3, 4);
	g.printGraph();
};

//邻接多重表
//有v个顶点组成的数组
//有一系列边节点
//每个顶点包含的信息是：数据，第一入边，第一出边
//每个边节点包含的信息是：tail，head，colLink (同tail), rowLink (同head)
//前向说明
class MyGraph;
class MyGraphEdge {
	friend class MyGraph;
private:
	int tail;
	int head;
	MyGraphEdge* path1;
	MyGraphEdge* path2;
	bool marked;
	MyGraphEdge(int tail, int head) : marked(false), tail(tail), head(head), path1(nullptr), path2(nullptr) {}
};
typedef MyGraphEdge* Edgeptr;
class MyGraph {
private :
	int n;//边数
	int e;//顶点个数
    Edgeptr* adjMultipleList;//节点的头指针
public:

};