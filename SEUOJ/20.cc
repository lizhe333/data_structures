#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
//01背包问题
//用一个dp[n]数组表示背包总共的大小
//dp[i]表示的是，如果背包的大小是i，则可以装的最大的价值是dp[i]
//转移方程，如果要拿下一件宝石，那么dp[k] = max(dp[k],dp[k-weight[i]]+value[i])
//意思是，如果背包大小为k,现在如果不拿第i件宝石，那么最大价值是dp[k]
//如果拿第i件宝石，那么最大价值是dp[k-weight[i]]+value[i]
//取这两个中的较大值，就是dp[k]
//最后，dp[n]就是答案

int solution(vector<pair<int,int>>& gems,int numbers,int size){
    //pair<int,int> 前一个表示大小，后一个是价值
    //创建一个容量数组
    vector<int> bags(size+1,0);

    //双层遍历，外部遍历宝石，内部遍历背包容量
    for(int i=0;i<numbers;i++){
        for(int j=size;j>gems[i].first;j--){
            //转移方程
            bags[j]=max(bags[j],bags[j-gems[i].first]+gems[i].second);
    }
    }
    //最终返回最大价值
    return bags[size];
};

int main(){
    int M;
    if (!(cin >> M)) return 0; 
    while (M--) {
        int N, C;
        cin >> N >> C;
        vector<pair<int, int>> gems(N);
        for (int i = 0; i < N; i++) {
            cin >> gems[i].first >> gems[i].second;
        }
        cout << solution(gems, N, C) << endl;
    }

    return 0;
}
