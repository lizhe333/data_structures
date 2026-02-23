/*
给你一个整数数组 nums 和一个整数 k ，请你统计并返回 该数组中和为 k 的子数组的个数 。
子数组是数组中元素的连续非空序列。
*/
#include <vector>
using namespace std;
//暴力解法，时间复杂度O(n^2)，会超时
// class Solution {
// public:
//     int subarraySum(vector<int>& nums, int k) {
//         //使用暴力遍历
//         int count =0;
//         int n=nums.size();
//         for(int start=0;start<n;start++){
//             int sum=0;
//             for(int end=start;end<n;end++){
//                 sum+=nums[end];
//                 if(sum==k){
//                     count++;
//                 }
//             }
//         }
//         return count;
//     }
// };
//前缀和+哈希表，时间复杂度O(n)，空间复杂度O(n)
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
     
};