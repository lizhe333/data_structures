#include <iostream>
#include <queue>   // 1. 包含标准队列头文件
#include <stack>   //    包含标准栈头文件 (用于打印路径)

// Point 结构体现在很简单
struct Point {
    int x;
    int y;
};

// Move 结构体保持不变
struct Move {
    int x;
    int y;
};

const int MAZE_WIDTH = 10;
const int MAZE_HEIGHT = 10;

// 迷宫数据保持不变
int maze[MAZE_HEIGHT][MAZE_WIDTH] = {
    {1,1,1,1,1,1,1,1,1,1}, {1,0,0,1,0,0,0,1,0,1}, {1,0,0,1,0,0,0,1,0,1}, {1,0,0,0,0,1,1,0,0,1},
    {1,0,1,1,1,0,0,0,0,1}, {1,0,0,0,1,0,0,0,0,1}, {1,0,1,0,0,0,1,0,0,1}, {1,0,1,1,1,0,1,1,0,1},
    {1,1,0,0,0,0,0,0,0,1}, {1,1,1,1,1,1,1,1,1,1}
};



void printShortestPath(Point start, Point end, Point predecessor[MAZE_HEIGHT + 2][MAZE_WIDTH + 2]) {
    // 使用 std::stack 来反转路径并打印
    std::stack<Point> pathStack;
    Point current = end;

    while (current.x != start.x || current.y != start.y) {
        pathStack.push(current);
        current = predecessor[current.x][current.y];
    }
    pathStack.push(start);

    std::cout << "找到最短路径 (从起点到终点):" << std::endl;
    while (!pathStack.empty()) { // 使用 .empty()
        Point p = pathStack.top(); // 使用 .top()
        std::cout << "(" << p.x - 1 << ", " << p.y - 1 << ")";
        pathStack.pop(); // 使用 .pop()
        if (!pathStack.empty()) {
            std::cout << " -> ";
        }
    }
    std::cout << "\n终点" << std::endl;
}


// 迷宫解法
bool soveMaze(int maze[MAZE_HEIGHT][MAZE_WIDTH], Point start) {
    int flag[MAZE_HEIGHT + 2][MAZE_WIDTH + 2];
    for (int i = 0; i < MAZE_HEIGHT + 2; i++) {
        for (int j = 0; j < MAZE_WIDTH + 2; j++) {
            if (i == 0 || j == 0 || i == MAZE_HEIGHT + 1 || j == MAZE_WIDTH + 1) {
                flag[i][j] = 1;
            }
            else {
                flag[i][j] = maze[i - 1][j - 1];
            }
        }
    }

    start.x++;
    start.y++;
    Point end = { 8 + 1, 8 + 1 };

    Move move[4] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
    //创建工作队列
    std::queue<Point> q;
    //创建一个前驱节点的数组
    //这样可以用来记录路径
    flag[start.x][start.y] = 2;
    Point predecessor[MAZE_HEIGHT + 2][MAZE_WIDTH + 2];
    q.push(start);
    bool found = 0;
    while (!q.empty()) {
        Point current = q.front();
        q.pop();
        //取出节点

        //先要判断当前节点是不是重点
        if (current.x == end.x && current.y == end.y) {
            printShortestPath(start, end, predecessor);
            return true;
        }
        for (int i = 0; i < 4; i++) {
            //遍历当前节点的相邻节点
            int gx = current.x + move[i].x;
            int gy = current.y + move[i].y;
            //判断如果不是墙
            if (flag[gx][gy] == 0) {
                //把这个点入队列
                q.push({ gx, gy });
                flag[gx][gy] = 2;
                predecessor[gx][gy] = current;
            }



        }

    }
    if (found) {
        std::cout << "已到达终点!" << std::endl;
        printShortestPath(start, end, predecessor);
        return true;
    }
    else {
        std::cout << "未找到路径。" << std::endl;
        return false;
    }
};

int main() {
    Point startPoint = { 1, 1 };

    std::cout << "正在使用广度优先搜索 (BFS) 和 C++ STL 队列解决迷宫..." << std::endl;
    if (soveMaze(maze, startPoint)) {
        std::cout << "\n成功解决迷宫!" << std::endl;
    }
    else {
        std::cout << "\n无法找到走出迷宫的路径。" << std::endl;
    }
    return 0;
}