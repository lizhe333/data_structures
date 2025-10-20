//#include<iostream>
//#include"Stack.h"
//using namespace std;
//struct Point
//{
//	int x;
//	int y;
//    int direction;
//    
//};
//
//struct  Move
//{
//    int x;
//    int y;
//};
//
//
//const int MAZE_WIDTH = 10;
//const int MAZE_HEIGHT = 10;
//
//int maze[MAZE_HEIGHT][MAZE_WIDTH] = {
//    {1,1,1,1,1,1,1,1,1,1},
//    {1,0,0,1,0,0,0,1,0,1},
//    {1,0,0,1,0,0,0,1,0,1},
//    {1,0,0,0,0,1,1,0,0,1},
//    {1,0,1,1,1,0,0,0,0,1},
//    {1,0,0,0,1,0,0,0,0,1},
//    {1,0,1,0,0,0,1,0,0,1},
//    {1,0,1,1,1,0,1,1,0,1},
//    {1,1,0,0,0,0,0,0,0,1}, // 终点 E 在 (8,8)
//    {1,1,1,1,1,1,1,1,1,1}
//};
//
//bool SoveMaze(int maze[MAZE_HEIGHT][MAZE_WIDTH], Point start) {
//    //传入迷宫和起点
//    int flag[MAZE_HEIGHT + 2][MAZE_WIDTH + 2];
//    //初始化迷宫
//    for (int i = 0; i < MAZE_HEIGHT + 2; i++) {
//        //上下多一行，设置边界
//        for (int j = 0; j < MAZE_WIDTH + 2; j++) {
//            if (i == 0 || j == 0 || i == MAZE_HEIGHT + 1 || j == MAZE_WIDTH + 1) {
//                //上下左右边界设置为1
//                flag[i][j] = 1;
//            }
//            else {
//                flag[i][j] = maze[i - 1][j - 1];
//            }
//
//        }
//    }
//    //调整起点
//    start.x++;
//    start.y++;
//    //调整终点
//    Point end = { 8 + 1,8 + 1,0 };
//    //创建工作栈
//    Stack<Point> stack;
//    //将起点压入栈
//    stack.push(start);
//
//
//
//    //起点设置为已访问 
//    Move move[4] = { {0, -1}, {1, 0}, {0, 1}, {-1, 0} };
//
//    //标记走过的点的值为2
//    flag[start.x][start.y] = 2;
//    while (!stack.isEmpty()) {
//
//        Point currentPoint = stack.gettop();
//        stack.pop();
//        //先检查有没有到终点
//
//        if (currentPoint.x == end.x && currentPoint.y == end.y) {
//            cout << "找到终点" << endl;
//            stack.push(currentPoint);//把终点压入栈
//            return true;
//        }
//
//
//        for (int i = currentPoint.direction; i < 4; i++) {
//            //当前还有方向可以走
//
//            int g = currentPoint.x + move[i].x;
//            int h = currentPoint.y + move[i].y;
//            if (flag[g][h] == 0 && maze[g][h] == 0) {
//                //找到一个合法的方向和点位
//                currentPoint.direction = i + 1;//记录下当前该点探索到哪个方向了，下一次可以继续探索
//                stack.push(currentPoint);
//                flag[g + 1][h + 1] = 2;
//                currentPoint.x = g;
//                currentPoint.y = h;
//                currentPoint.direction = 0;
//                break;
//            }
//
//
//        }
//    }
//};
    //int main() {
    //    // The entrance to the maze is at (1,1) in the original coordinate system.
    //  // The direction is initialized to 0.
    //    Point startPoint = { 1, 1, 0 };

    //    cout << "Attempting to solve the maze..." << endl;

    //    if (SoveMaze(maze, startPoint)) {
    //        cout << "\nMaze solved successfully!" << endl;
    //    }
    //    else {
    //        cout << "\nCould not find a path through the maze." << endl;
    //    }

    //    return 0;
    //}