//汉诺塔问题
//问题分析：使用递归解决
#include<iostream>
using namespace std;
void move(char A,char B){
    cout<< A<<"->"<<B<<endl;
}
void Solution(int n,char A,char B,char C){
    if(n==1){
        move(A,C);
    }
    //输入是需要移动的目标盘子的个数
    //该问题可以被分解成,以n-1个盘子以B为起点，移动一次A->C,然后以B为起点的
    //以A为跳板，移动到C，递归地完成
    Solution(n-1,A,C,B);
    move(A,C);
    Solution(n-1,B,A,C);
}
int main(){
    char A='A';
    char B='B';
    char C='C';
    int n;
    cin>>n;
    Solution(n,A,B,C);
    return 0;
}