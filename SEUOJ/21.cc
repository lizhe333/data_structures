#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;
typedef long long ll;
//矩阵连乘问题
//用动态规划，状态转移方程，本质上就是看把最后一个乘号放在哪，乘号左右两边的代价，加上相乘的代价，就是现在的代价

struct Matrix{
    int row,col;
};
ll Min_cost_plus_matrix(vector<Matrix> &matrix,int n){
    //动态规划数组
    vector<vector<ll>>dp(n+1,vector<ll>(n+1,0));
    //连乘长度为l的矩阵
    for(int l=2;l<=n;l++){
        for(int i=1;i<=n-l+1;i++){
            int j=i+l-1;
            dp[i][j]=-1;//初始化标记
            for(int k=i;k<j;k++){
                ll cost= dp[i][k]+dp[k+1][j]+matrix[i].row*matrix[k].col*matrix[j].col;
                if(dp[i][j]==-1||cost<dp[i][j]){
                dp[i][j]=cost;
            }
            }            
        }
    }
    return dp[1][n];
}
int main() {
    int M;
    if (!(cin >> M)) return 0;
    while (M--) {
        int N;
        if (!(cin >> N)) break;
        vector<Matrix> matrix(N + 1);
        for (int i = 1; i <= N; i++) {
            cin >> matrix[i].row >> matrix[i].col;
        }

        cout << Min_cost_plus_matrix(matrix, N) << endl;
    }
    return 0;
}