//批处理调度
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int best_sum = 1e9;
void dfs(bool *visited,int step,int t1,int t2,int current_sum,int n,int *a,int *b){
    //剪枝
    if(current_sum>=best_sum){
        return;
    }
    if(step==n){
        best_sum=current_sum;
        return ;
    }
    //开始尝试，接下来各个任务的分配可能
    for(int i=0;i<n;i++){
        if(!visited[i]){
            visited[i]=true;
            int next_t1=t1+a[i];
            int next_t2=max(t2,next_t1)+b[i];
            int next_current_sum=current_sum+next_t2;
            dfs(visited,step+1,next_t1,next_t2,next_current_sum,n,a,b);
            visited[i]=false;
        }
    }

}

int main() {
    // 优化标准输入输出流速度
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    // 使用 while 读取，以防 OJ 包含多组测试用例
    while (cin >> n) {
        // 由于是 n! 级别的回溯，n 一般不会超过 20，开 50 大小绰绰有余
        int a[50];
        int b[50];
        bool visited[50] = {false}; // 初始化全是 false

        // 读取每个作业在机器1和机器2上的加工时间
        for (int i = 0; i < n; i++) {
            cin >> a[i] >> b[i];
        }
        best_sum = 1e9; 
        dfs(visited, 0, 0, 0, 0, n, a, b);
        cout << best_sum << "\n";
    }
    return 0;
}