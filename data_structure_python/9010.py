import sys

class Edge:
    def __init__(self,u,v,weight):
        self.u = u
        self.v = v
        self.weight = weight

#定义一个并查集
parent=[]

#实现查找和路径压缩的函数
def find(x):
    if parent[x]==x:
        return x
    else:
        parent[x]=find(parent[x])
        return parent[x]

#定义合并函数
def union(x,y):
    root_x=find(x)
    root_y=find(y)
    
    if root_x!=root_y:
        parent[root_x]=root_y
        return True
    return False

def kruskal(n,edges):
    #声明将要使用全局的parent的列表
    global parent
    
    edges.sort(key = lambda edge:edge.weight)#表明排序的键是edges的weight作为edge
    
    #先初始化独立的parent列表
    parent=[i for i in range(n+1)]
    
    total_weight =0
    edge_count = 0
    
    for edge in edges:
        if find(edge.u) != find(edge.v):
            union(edge.u, edge.v)
            total_weight += edge.weight
            edge_count += 1
            
        # 步骤 6: 优化 (当边数达到 n-1 时停止)
        if edge_count == n - 1:
            break
    return total_weight

def main():
    try:
        T=int(sys.stdin.readline())
    except ValueError:
        T=0
    for _ in range(T):
        # C++: int n, m; std::cin >> n >> m;
        try:
            line = sys.stdin.readline().split()
            if not line:
                continue # 跳过空行
            n, m = map(int, line)
        except (ValueError, IndexError):
            continue # 处理格式错误的行

        # C++: std::vector<Edge> edges(m); ...
        edges = []
        for _ in range(m):
            try:
                u, v, weight = map(int, sys.stdin.readline().split())
                edges.append(Edge(u, v, weight))
            except (ValueError, IndexError):
                continue # 处理格式错误的行

        # C++: long long mst_weight = Kruskal(n, edges);
        mst_weight = kruskal(n, edges)
        
        # C++: std::cout << mst_weight << std::endl;
        print(mst_weight)
if __name__ == '__main__':
    main()