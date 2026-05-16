#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
//动态规划求解最大子段和
int maxSubArray(vector<int>&nums){
    int n=nums.size();
    //遍历一遍，用一个另外的数组dp，dp[i]表示以nums[i]结尾的最大子段和
    vector<int> res(n,0);
    res[0] = max(0, nums[0]);
    for(int i=1;i<n;i++){
        res[i]=max(nums[i],res[i-1]+nums[i]);
        if(res[i]<0){
            res[i]=0;
        }
    }
    //返回dp数组中的最大值
    int max=res[0];
    for(int i=1;i<n;i++){
        if(res[i]>max){
            max=res[i];
        }
    }
    return max;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    if (!(cin >> n)) return 0;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    cout << maxSubArray(nums) << endl;
    return 0;
}