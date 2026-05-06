// 给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。

// 请注意 ，必须在不复制数组的情况下原地对数组进行操作。
#include <vector>
using namespace std;
#include <iostream>
#include <algorithm>

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        //快指针一直往前跑，慢指针之后在非0的时候才向前跑，记录非零序列的最后的位置
        int slow=0;
        for(int i=0;i<nums.size();i++){
            if(nums[i]!=0){
                swap(nums[slow],nums[i]);
                slow++;
            }
        }
    }
};