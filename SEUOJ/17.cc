#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
bool solution(vector<int>&nums,int target){
    //先对数组进行一次排序
    sort(nums.begin(),nums.end());
    //使用双指针进行解决
    int right=nums.size()-1,left=0;
    while(left<right){
        int sum=nums[left]+nums[right];
        if(sum==target){
            return true;
        }
        else if(sum>target){
            right--;
        }
        else{
            left++;
        }
    }
    return false;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int M;
    if (!(cin >> M)) return 0; 
    while (M--) {
        int N, X;
        if (!(cin >> N >> X)) break; // 读取元素个数 N 和目标和 X
        vector<int> nums(N);
        for (int i = 0; i < N; ++i) {
            cin >> nums[i]; // 读取 N 个整数
        }
        if (solution(nums, X)) {
            cout << "yes" << endl;
        } else {
            cout << "no" << endl;
        }
    }
    return 0;
}