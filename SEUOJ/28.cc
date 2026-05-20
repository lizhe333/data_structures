#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
struct Activity{
    int start,finish,value;
};

//写一个比较函数，按照结束时间进行排序
bool compare(Activity a,Activity b){
    return a.finish<b.finish;
}
//用二分查找来实现找一个i前面的活动，结束时间最晚的活动,返回记录的是下标
int find_pre_last(vector<Activity> &activities,int i){
    //活动是已经排序好了的
    int target=activities[i].start;
    int left=1;//从下标1开始二分搜索，第一个活动的下标就是1
    int right=i-1;
    int p=0;
    //找一个结束时间 <= 当前活动开始时间 的“最后一个”活动的下标
    while(left<=right){
        int mid=left+(right-left)/2;
        if(activities[mid].finish<=target){
            p=mid;
            left=mid+1;
        }
        else{
            right=mid-1;
        }
    }
    return p;//p=0时候找不到兼容的活动，需要在下面的程序中进行单独处理
}


int Max_value_activity(vector<Activity> &activities){
    int n=activities.size()+1;
      activities.push_back(Activity{-1,-1,0});//插入哨兵节点
    //首先按照结束时间进行排序
    sort(activities.begin(),activities.end(),compare);
    //完善p数组
  
    vector<int> p(n,0);
    for(int i=1;i<n;i++){
        p[i]=find_pre_last(activities,i);
    }

    //开始动态规划
    vector<int>dp(n,0);
    for(int i=1;i<n;i++){
            dp[i]=max(dp[i-1],activities[i].value+dp[p[i]]);
          
    }
    return dp[n-1];
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int M;
    if (cin >> M) {
        while (M--) {
            int N;
            cin >> N;
            vector<Activity> activities(N);
            for (int i = 0; i < N; i++) {
                cin >> activities[i].start >> activities[i].finish >> activities[i].value;
            }
            cout << Max_value_activity(activities) << "\n";
        }
    }
    return 0;
}