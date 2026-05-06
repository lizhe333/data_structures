#include<iostream>
#include<vector>
using namespace std;
void Pop(vector<int>& nums){
    int size=nums.size();
    for(int i=0;i<size;i++){
        for(int j=0;j<size-i;j++){
            if(nums[j]>nums[j+1]){
                int temp=nums[j];
                nums[j]=nums[j+1];
                nums[j+1]=temp;
            }
        }
    }
    for(int i=0;i<size;i++){
        cout<< nums[i];
    }
    cout<<endl;
}

int main() {
    int m;
    cin >> m;
}