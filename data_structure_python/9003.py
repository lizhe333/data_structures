import sys
# 【【【非常重要！！！】】】
# 100x100 的地图有 10000 个格子
# DFS 的递归深度可能达到 10000
# Python 默认的 1000 绝对不够用
# 我们需要手动调高递归深度限制
sys.setrecursionlimit(100 * 100 + 10)

directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]
def dfs(r, c, n, m, grid, visited):
    if r < 0 or r >= n or c < 0 or c >= m or visited[r][c] or grid[r][c] == '#':
        return
    visited[r][c] = True
    for dx, dy in directions:
        dfs(r + dx, c + dy, n, m, grid, visited)
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

        for r in range(n):
            row_str = sys.stdin.readline().strip()
            grid.append(row_str)
            for c in range(m):
                if row_str[c] == 'S':
                    start_r, start_c = r, c
                elif row_str[c] == 'G':
                    goal_r, goal_c = r, c
        
        # 准备 visited 数组
        #这行代码的解释：
        #_是一个站位符，意味着忽略这个值
        #生成的二维数组当中就都是False
        visited = [[False for _ in range(m)] for _ in range(n)]

        # 2. 从起点开始 DFS
        dfs(start_r, start_c, n, m, grid, visited)

        # 4. 得出结论
        if visited[goal_r][goal_c]:
            print("exist!")
        else:
            print("not exist!")
            
        return True
    except EOFError:
        return False
    except Exception as e:
        # print(f"An error occurred: {e}", file=sys.stderr)
        return False
# def main():
#     try:
#         T_str = sys.stdin.readline()
#         if not T_str:
#             return
#         T = int(T_str.strip())
        
#         for _ in range(T):
#             solve()
            
#     except Exception as e:
#         pass

# if __name__ == "__main__":
#     main()