#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

//来获取一个像素值需要用的bit位
int getBit(int n){
  
    int k=1;
    n=n/2;
    while(n>0){
        k++;
        n=n/2;
    }
    return k;
}

int findMaxBit(int satrt,int end,vector<int>& b){
    int maxBit=0;
    //遍历从start到end的像素点
    for(int i=satrt;i<=end;i++){
        maxBit=max(maxBit,b[i]);
    }
    return maxBit;
}


//point数组用来记录像素像素点的大小
//用S[i]来表示从像素1~i的存储的最优解

//b[i]数组用来记录第i个像素点的bit位
vector<int>  compress(vector<int>&point){
    int n=point.size();
    //初始化S数组
    vector<int> S(n+1,0x3f3f3f3f);

    //初始化b数组
    vector<int> b(n+1,0);
    //初始化S[0]为0
    S[0]=0;
    b[0]=0;
    //遍历来得到原始的b数组
    for(int i=1;i<=n;i++){
        b[i]=getBit(point[i-1]);
    }

    for(int i=1;i<=n;i++){
        int  end_index=0;
        if(i>=255){
            end_index=255;
        }else{
         end_index=i;
        }

        for(int k=end_index;k>=1;k--){
            //状态转移方程
            S[i]=min(S[i-k]+k*findMaxBit(i-k+1,i,b)+11,S[i]);
        }
    }
    return S;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    if (!(cin >> n)) return 0;
    vector<int> point(n);
    for (int i = 0; i < n; i++) {
        cin >> point[i];
    }
    vector<int> result = compress(point);
    cout << result[n] << "\n";
    return 0;
}
