//旅行商最近邻问题
#include <iostream>
#include <vector>
using namespace std;
int FindNextCity(vector<vector<int>>&matrix,int nums,int cur_city,vector<bool>&visited){
    int min_index=-1;
    for(int j=1;j<=nums;j++){
        if(!visited[j]&&(min_index==-1||matrix[cur_city][j]<matrix[cur_city][min_index])){
            min_index=j;
        }
    }
    if(min_index==1){
        return -1;
    }
    return min_index;
}
int solution(vector<vector<int>> &matrix,int nums){
    //每次都从城市1出发
    //martix[i][j]表示城市i到城市j的距离
    int sum=0;
    //创建一个数组用于标记是否访问过
    vector<bool> visited(nums+1,false);
    visited[1]=true;
    int cur_city=1;
    for(int step=1;step<nums;step++){
        int next_city=FindNextCity(matrix,nums,cur_city,visited);
        sum+=matrix[cur_city][next_city];
        visited[next_city]=true;
        cur_city=next_city;
    }
    //返回最后一个城市
    sum += matrix[cur_city][1];
    return sum;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    // 持续读取输入，直到没有数据
    while (cin >> n) {
        vector<vector<int>> matrix(n + 1, vector<int>(n + 1));
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                cin >> matrix[i][j];
            }
        }
        cout << solution(matrix, n) << "\n";
    }
    return 0;
}
