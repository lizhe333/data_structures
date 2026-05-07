//二维搜索矩阵，分治法代码
#include <vector>
#include <iostream>
using namespace std;

class Solution{
    public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if(matrix.empty()||matrix[0].empty()) return false;
        //一开始选择所有作为搜索目标区域
        return search(matrix,target,0,matrix.size()-1,0,matrix[0].size()-1);
    }
    private:
    bool search(vector<vector<int>>& matrix, int target,int row_start,int row_end,int col_start,int col_end){
        if(row_start>row_end||col_start>col_end) return false;
        //取中点
        int row_mid=(row_start+row_end)/2,col_mid=(col_start+col_end)/2;
        if(matrix[row_mid][col_mid]==target){
            return true;
        }
        else if(matrix[row_mid][col_mid]>target){
            //如果中点的值大于目标值，那么目标值只能在左上角的区域
            return search(matrix,target,row_start,row_mid-1,col_start,col_mid-1)||
                   search(matrix,target,row_start,row_mid-1,col_mid,col_end)||
                   search(matrix,target,row_mid,row_end,col_start,col_mid-1);
    }     else{
            //如果中点的值小于目标值，那么目标值只能在右下角的区域
            return search(matrix,target,row_mid+1,row_end,col_mid+1,col_end)||
                   search(matrix,target,row_start,row_mid,col_mid+1,col_end)||
                   search(matrix,target,row_mid+1,row_end,col_start,col_mid);
        }
    }
};
int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int nums;
    // 读取测试组数
    if (cin >> nums) {
        while (nums--) {
            int m, n, target;
            cin >> m >> n >> target;
            vector<vector<int>> matrix(m, vector<int>(n));
            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < n; ++j) {
                    cin >> matrix[i][j];
                }
            }
            Solution sol;
            if (sol.searchMatrix(matrix, target)) {
                cout << "true\n";
            } else {
                cout << "false\n";
            }
        }
    }
    return 0;
}