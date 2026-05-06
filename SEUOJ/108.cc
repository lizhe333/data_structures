//整数划分问题，用递归的方式解决
//q(n,m)表示n的划分数，m表示加数最多不超过m
//q(n,1)=1
//q(n,m)=q(n,n) m>=n
//q(n,n)=1+q(n,n-1) n==m
//q(n,m)=q(n,m-1)+q(n-m,m) n>m>1  //使用最大的加数m与不使用

#include<iostream>
using namespace std;
int Solution(int n,int m){
    //分割目标和最大分割数
    if(m==1){
        return 1;
    }
    else if(m>n){
        return Solution(n,n);
    }else if(n==m){
        return 1+Solution(n,n-1);
    }
    else{
        return  Solution(n,m-1)+Solution(n-m,m);
    }
}
int main(){
    int n;
    cin>> n;
    cout<< Solution(n,n);
}