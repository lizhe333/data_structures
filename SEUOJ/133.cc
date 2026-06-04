//01背包问题，用回溯法解决
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

//辅助函数用于处理回溯和剪枝
void backtrack(int curr_w,int curr_v,int curr_index,vector<int>&w,vector<int>&v,int& max_v,vector<int>&suffix_sum,int n,int W){
    if(curr_index==n){
        //递归到底了
        if(curr_v>max_v){
            max_v=curr_v;
        }
        return ;//所有物品都做过判断了
    }
    //尝试装入左枝
    if(curr_w+w[curr_index]<=W){
        backtrack(curr_w+w[curr_index],curr_v+v[curr_index],curr_index+1,w,v,max_v,suffix_sum,n,W);
    }
    //尝试装入右枝
    //先用后缀数组和判断，潜在的最大价值是否能超过当前最大价值，如果不能就剪枝
    int remain_potential=(curr_index+1<n) ? suffix_sum[curr_index+1] : 0;//剩余物品的潜在最大价值
    if(curr_v+remain_potential>max_v){
        backtrack(curr_w,curr_v,curr_index+1,w,v,max_v,suffix_sum,n,W);
    }
}


//主函数
int solution(vector<int>& w,vector<int>& v,int W,int n){
    if(n<=0||W<=0){
        return 0;
    }

    //创建后缀数组和
    vector<int>suffix_sum(n+1,0);
    suffix_sum[n - 1] = v[n - 1];
    for (int i = n - 2; i >= 0; --i) {
        suffix_sum[i] = suffix_sum[i + 1] + v[i];
    }
    int max_v=0;
    backtrack(0,0,0,w,v,max_v,suffix_sum,n,W);
    return max_v;
}


int main() {
    int n, B;

    if (!(cin >> n >> B)) return 0;
    
    vector<int> w(n);
    vector<int> v(n);

    for (int i = 0; i < n; ++i) {
        cin >> w[i] >> v[i];
    }

    int result = solution(w,v,B,n);
    
    cout << result << endl;

    return 0;
}