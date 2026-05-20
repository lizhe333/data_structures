//插入乘号，线性DP问题
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

long long solution(vector<int>&A,int n){
    int nums=A.size();
    int ops=n;//乘号的数目

    //为了节约开销，保存一个前缀和数组
    vector<long long >S(nums+1,0);
    for(int i=1;i<=nums;i++){
        S[i]=S[i-1]+A[i-1];
    }
    vector<vector<long long>>dp(nums+1,vector<long long>(ops+1,0));//全部初始化为0

    //当没有乘号的时候是前缀和
    for(int i=1;i<=nums;i++){
        dp[i][0]=S[i];
    }
    //外层循环，逐步增加乘号的个数
    for(int i=1;i<=ops;i++){
        //中间层，至少需要j+1个数字才能插入下j个乘号
        for(int j=i+1;j<=nums;j++){
            //现在数字个数是j,乘号个数是i
            //计算后半段的求和
            //m就代表最后一个乘号插入的位置
            for(int m=i+1;m<=j;m++){
                dp[j][i]=max(dp[j][i],dp[m-1][i-1]*(S[j]-S[m-1]));
            }
        }
    }
    return dp[nums][ops];

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int M;
    // 读取测试组数 M，并检查是否成功读取
    if (cin >> M) {
        // 循环处理每一组测试数据
        while (M--) {
            int N, K;
            cin >> N >> K;
            vector<int> A(N);
            for (int i = 0; i < N; ++i) {
                cin >> A[i];
            }
            cout << solution(A, K) << "\n";
        }
    }
    return 0;
}