#include<iostream>
#include<vector>
using namespace std;

int findTarget(vector<int>& nums,int target){
    //输入的是一个递增的数组
    //输出的是父节点
    int size = nums.size(); 
    int father=-1;//记录父亲节点的值
    int left=0,right=size-1;
    bool found=false;
    while(left<=right){
        int mid=left+(right-left)/2;
        if(nums[mid]==target){
            found=true;
            break;
        }else if(nums[mid]<target){
            father=nums[mid];
            left=mid+1;
            continue;
        }else{
            father=nums[mid];
            right=mid-1;
            continue;
        }
    }

    if (found) {
        cout << "success, father is " << father << "\n";
    } else {
        cout << "not found, father is " << father << "\n";
    }
    return father;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int M;
    if (cin >> M) {
        while (M--) {
            int N, X;
            cin >> N >> X; 
            vector<int> nums(N);
            for (int i = 0; i < N; ++i) {
                cin >> nums[i]; // 读入递增数组
            }
            findTarget(nums, X);
        }
    }
    return 0;
}