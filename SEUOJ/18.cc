#include <iostream>
#include <vector>
using namespace std;

//写一个merge函数
void merge(vector<int> &A,int start,int mid,int end,int & res){
    //start到mid和mid到end都已经是有序的了
    //先创建一个临时数组存储
    vector<int> temp(end-start+1);
    //左右两个数组的其实指针
    int i=start,j=mid+1;
    int k=0;
    while(i<=mid && j<=end){
        if(A[i]<=A[j]){
            temp[k++]=A[i++];
        }
        else{
            //A[j]小，比左边的i后面的都小，由于马上要被拿走了，所以要算上逆序对的个数
            res+=mid-i+1;
            temp[k++]=A[j++];
        }
    }
    while(i<=mid){
        //左边还没有遍历完。
        temp[k++]=A[i++];
    }
    while(j<=end){
        //右边还没有遍历完。
        temp[k++]=A[j++];
    }
    //将临时数组中的数据复制回原数组
    for(int i=0;i<k;i++){
        A[start+i]=temp[i];
    }
}

//逆序对问题
void solution(vector<int> &A,int & res,int start,int end){
    int mid = start + (end - start) / 2;
    //用递归的方式
    if(start>=end){
        return;
    }
    else{
        solution(A,res,start,mid);
        solution(A,res,mid+1,end);
        merge(A,start,mid,end,res);
    }

}

int main() {
    // 优化输入输出效率
    ios::sync_with_stdio(false);
    cin.tie(0);
    int m;
    if (!(cin >> m)) return 0; // 读取测试组数

    while (m--) {
        int n;
        if (!(cin >> n)) break; // 读取当前组的焊点个数

        vector<int> A(n);
        for (int i = 0; i < n; i++) {
            cin >> A[i]; // 读取右侧连接点序列 xi
        }  
        int res = 0;
        if (n > 1) {
            solution(A,res, 0, n - 1);
        }
        cout << res << endl;
    }

    return 0;
}