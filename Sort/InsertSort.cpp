#include <iostream>
void Insert( const int a ,int A[],int b ){
 
   A[0] = a;//将a插入A[1..b]的有序序列当中
 
  while(A[b]>a){
    //左移
    //把比a大的元素A[b]向右移动
    A[b+1] = A[b];
    b--;
  }
  A[b+1] = a;//所以实际上并非真的移动a只是一个a的替身指针在移动
}

void InsertSort(int *A,int n){
    for(int i=2;i<=n;i++){
        //从第二项开始不断往前插入
        int temp = A[i];
        Insert(temp,A,i-1);
    }
}