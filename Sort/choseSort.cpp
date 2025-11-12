using namespace std;
#include <iostream>
#include <utility>
void choseSort(int* A,int n,int j){
    //索引从1~n
    for(int i = 0;i<=n-2;i++){
        //遍历后续的每个找到最小的元素的位置
        int min_index = i;
        for(int j = i+1;j<=n-1;j++){
            if(A[j]<A[min_index]){
                min_index = j;
            }
        }

        //交换两个元素
        if(i!=min_index){
            // int temp = A[i];
            // A[i] = A[min_index];
            // A[min_index] = temp;
            swap(A[i],A[min_index]);
        }
    }
}