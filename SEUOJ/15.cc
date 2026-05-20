#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
//最大子数组和。
//递推函数是，加入a[i]，看看是否会增大最大子数组和。
//如果增大，就加入a[i]，否则不加入。

int max_subarray_sum(vector<int>& a) {
    //记录一个全局的最大值
    int max_sum=a[0];
    int n=a.size();
    //创建一个大小相同的数组来记录最大子数组和
    vector<int> dp(n,0);
    dp[0] = a[0];

    for(int i=0;i<n;i++){
        dp[i]=a[i];
        dp[i]=max(dp[i],dp[i-1]+a[i]);

        if(dp[i]>max_sum){
            max_sum=dp[i];
        }
    }
    return max_sum;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int m;
    if (cin >> m) {
        while (m--) {
            int n;
            if (cin >> n) {
                vector<int> a(n);
                for (int i = 0; i < n; i++) {
                    cin >> a[i];
                }
                cout << max_subarray_sum(a) << endl;
            }
        }
    }
    return 0;
}