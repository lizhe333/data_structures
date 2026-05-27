//多机装载问题
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int Solution(vector<int> tasks,int m){
    //先将任务按照时间排序，从大到小排序
    sort(tasks.begin(),tasks.end(),greater<int>());
    //对每个机器，优先分配时间长的任务，同时也要判断是否可以加入
    //用一个数组来记录每个机器结束的时间
    vector<int> end_time(m,0);
    for(int i=0;i<tasks.size();i++){
        //每次都找最早结束时间的机器
        int min_index=0;
        for(int j=1;j<m;j++){
            if(end_time[j]<end_time[min_index]){
                min_index=j;
            }
        }
        //将当前任务加入到这个机器上
        end_time[min_index]+=tasks[i];
    }
    //现在所有任务都分配完成，遍历所有机器，找到最晚结束的
    int max_load=0;
    for(int i=0;i<m;i++){
        if(end_time[i]>max_load){
            max_load=end_time[i];
        }
    }
    return max_load;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; 
    // n 是作业数量，m 是机器数量
    if (cin >> n >> m) {
        vector<int> tasks(n); 
        for(int i = 0; i < n; i++){
            cin >> tasks[i];
        }

        cout << Solution(tasks, m) << "\n";
    }
    
    return 0;
}