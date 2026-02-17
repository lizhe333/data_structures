//对一个m行n列的矩阵进行顺时针的螺旋遍历
#include <iostream>
#include <vector>
#include <algorithm>
/*
解题思路：首先定义上下左右边界，然后一直走，每次走到一个边界的话就重新缩小边界
例如先走完第一行，那么上边界就缩小一行，接着走完最后一列，那么右边界就缩小一列，以此类推
如果重新定义边界之后，发现边界重叠了，那么说明已经遍历完了，直接返回结果即可
*/
using namespace std;
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> res;
        if(matrix.empty()) return res;
        int n=matrix.size();
        int m=matrix[0].size();
        //一个n行m列的矩阵，进行螺旋遍历
        int left=0,right=m-1,top=0,bottom=n-1;
        while(true){
            for(int i=left;i<=right;i++){ //先从左向右走
                res.push_back(matrix[top][i]);
            }
            top++;
            if(top>bottom) break;
            for(int i=top;i<=bottom;i++){ //再从上向下走
                res.push_back(matrix[i][right]);
            }
            right--;
            if(left>right) break;
            for(int i=right;i>=left;i--){ //再从右向左走
                res.push_back(matrix[bottom][i]);
            }
            bottom--;
            if(top>bottom) break;
            for(int i=bottom;i>=top;i--){ //最后从下向上走
                res.push_back(matrix[i][left]);
            }
            left++;
             if(left>right) break;
        }
        return res;
    }
};