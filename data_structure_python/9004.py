import sys
from collections import deque
def solve():
    try:
        # 1. 读取 n 和 m
        line = sys.stdin.readline().strip()
        if not line:
            return False
            
        n_str, m_str = line.split()
        n = int(n_str)
        m = int(m_str)

        grid = []
        start_r, start_c = -1, -1
        goal_r, goal_c = -1, -1
        
        #读取地图找到S和G
        for r in range(n):
            row_str = sys.stdin.readline().strip()
            grid.append(row_str)
            for c in range(m):
                if row_str[c] == 'S':
                    start_r, start_c = r, c
                elif row_str[c] == 'G':
                    goal_r, goal_c = r, c
        
        #准备数据结构
        q = deque()
        q.append((start_r, start_c))
        visited = [[-1 for _ in range(m)] for _ in range(n)]
        visited[start_r][start_c] = 0
        
        #定义方向
        directions=[(-1,0),(1,0),(0,-1),(0,1)]
        
        #开始探索
        while q:
            r, c = q.popleft()
            current_distance=visited[r][c]
            
            #如果到了重点则提前结束
            if r==goal_r and c==goal_c:
                break
            for dx, dy in directions:
                new_r= r+dx
                new_c= c+dy
                #如果新的点符合要求
                if 0<=new_r<n and 0<=new_c<m and grid[new_r][new_c]!='#' and visited[new_r][new_c]==-1:
                    q.append((new_r,new_c))
                    visited[new_r][new_c]=visited[r][c]+1
        
        print(visited[goal_r][goal_c])
        return True
    except EOFError:
        return False
    except Exception as e:
        # print(f"An error occurred: {e}", file=sys.stderr)
        return False
def main():
    """主函数，处理 T 组输入"""
    try:
        T_str = sys.stdin.readline()
        if not T_str:
            return
        T = int(T_str.strip())
        
        for _ in range(T):
            solve()
            
    except Exception as e:
        pass

if __name__ == "__main__":
    main()
