//n皇后问题
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int n;
int total_solutions=0;

//记录是否能够存放的状态数组
vector<bool> col_used, diag1, diag2;

void backtrace(int row){
    //成功放到第n行了，说明找到了一种解法
    if(row==n){
        total_solutions++;
        return;
    }
    //遍历列，尝试放皇后
    for(int col=0; col<n; col++){
        //检查当前列和对角线是否安全
        int d1_idx=row-col+n-1, d2_idx=row+col;
        if(!col_used[col]&&!diag1[d1_idx]&&!diag2[d2_idx]){
            //放置皇后
            col_used[col]=true;
            diag1[d1_idx]=true;
            diag2[d2_idx]=true;
            //递归放置下一行
            backtrace(row+1);
            //回溯，撤销放置
            col_used[col]=false;
            diag1[d1_idx]=false;
            diag2[d2_idx]=false;
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // 读取输入 n
    if (cin >> n) {
        col_used.assign(n, false);
        diag1.assign(2 * n, false); 
        diag2.assign(2 * n, false);

        backtrace(0);
        cout << total_solutions << "\n";
    }
    return 0;
}