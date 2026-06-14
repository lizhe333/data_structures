//集合覆盖问题
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int min_sum=1e9;

void dfs(vector<int>& visited,vector<vector<int>>& subsets,int  curr_step,int curr_sum,int subsets_numbers){
    //剪枝
    if(curr_sum>=min_sum){
        return;
    }
    //如果所有visited都为1，说明已经覆盖了所有元素
    bool flag=true;
    for(int i=0;i<visited.size();i++){
        if(visited[i]==0){
            flag=false;
            break;
        }
    }
    if(flag){
        min_sum=min(min_sum,curr_sum);
        return;
    }
    if (curr_step == subsets_numbers) {
        return;
    }
    for(auto j:subsets[curr_step]){
            visited[j]++;
        
      }
      //继续下一个点
      dfs(visited,subsets,curr_step+1,curr_sum+1,subsets_numbers);
    //回溯后再减去标记
    for(auto j:subsets[curr_step]){
            visited[j]--;
      }
      //如果不选择当前集合
      dfs(visited,subsets,curr_step+1,curr_sum,subsets_numbers);
      
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<int> visited(n, 0);
    vector<vector<int>> subsets(m);

    for (int i = 0; i < m; i++) {
        int count;
        cin >> count; // 读取该子集包含的元素个数
        
        for (int k = 0; k < count; k++) {
            int element;
            cin >> element;
            // 题目输入的元素是 1 到 n，为了和数组下标对应，我们存入时 - 1
            subsets[i].push_back(element - 1);
        }
    }
    dfs(visited, subsets, 0, 0, m);
    if (min_sum == 1e9) {
        cout << -1 << "\n";
    } else {
        cout << min_sum << "\n";
    }
    return 0;
}