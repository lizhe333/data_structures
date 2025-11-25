#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int Partition(vector<int>&a,int left,int right){
//首先选择一个基准，最左边的数字
int provt = a[left];
int i = left;
int j = right+1;
while(i<j){
  //从左向右找比provt大的数
  do{i++;}while(a[i]<provt&&i<right);
  //从右向左找比provt小的数
  do{j--;}while(a[j]>provt);
  //此时仍需判断一次他们的位置关系
  if(i<j){
      swap(a[i],a[j]);
  }

}
swap(a[left],a[j]);

return j;
}
void QuickSort(vector<int>&a,int left,int right){
  //注意这里的顺序一定是先进行分区，再执行partition函数  
  if(left>right){
    return;
  }
  int h = Partition(a,left,right);
  //写递归的终止条件

  QuickSort(a,left,h-1);
  QuickSort(a,h+1,right);
}

int main() {
    vector<int> arr = {26, 5, 37, 1, 61, 11, 59, 15, 48, 19};
    
    cout << "排序前: ";
    for (int num : arr) cout << num << " ";
    cout << endl;

    QuickSort(arr, 0, arr.size() - 1);

    cout << "排序后: ";
    for (int num : arr) cout << num << " ";
    cout << endl;

    return 0;
}