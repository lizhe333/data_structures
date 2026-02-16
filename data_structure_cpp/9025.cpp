#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
struct TreeNode{
    int bro;
    int son;
};
TreeNode tree[10005];
int getDepth(int curr){
    int max_child_depth = 0;

    //找到第一个孩子，开始遍历孩子

    int child = tree[curr].son;
    while(child != -1){
        max_child_depth = max(max_child_depth, getDepth(child));
        //找到下一个孩子，看看下一个孩子是不是深度更大

        child = tree[child].bro;
    }
    //树的深度是最大深度的子树的深度+1
    return max_child_depth + 1;
}

void solve(){
int n;
    cin >> n;
 
    for (int i = 0; i < n; ++i) {
        int id, son, bro;
        cin >> id >> son >> bro;
        tree[id].son = son;
        tree[id].bro = bro;
    }

    
    cout << getDepth(1) << endl;
}
int main() {

    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}