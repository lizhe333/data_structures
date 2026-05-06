#include <vector>
using namespace std;
#include <iostream>
#include <algorithm>
// 给定一个长度为 n 的整数数组 height 。有 n 条垂线，第 i 条线的两个端点是 (i, 0) 和 (i, height[i]) 。

// 找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。

// 返回容器可以储存的最大水量。
//使用贪心的策略。假设从最宽的容器开始，即左右两边，然后不断地找最高的容器。每次移动较短的边，直到两边重合。
// 时间复杂度为O(n)，空间复杂度为O(1)。
class Solution {
public:
    int maxArea(vector<int>& height) {
        int left=0;
        int right=height.size()-1;
        int maxArea=0;
        while(left<right){
            int s=min(height[left],height[right])*(right-left);
            maxArea=max(maxArea,s);
            if(height[left]<height[right]){
                left++;
            }
            else{
                right--;
            }
        }
        return maxArea;
    }
};