//黑白连线问题
//维护两个栈，分别存放黑点和白点，分别进行遍历，当遇到黑点，就将白点的栈顶弹出，这样就是离的最近的
#include <iostream>
#include<stack>
#include<vector>
using namespace std;

int Solution(vector<int> P){
    //P当中有2n个点，1是黑点，0是白点
    stack<int> black,white;
    int size=P.size();
    int n=size/2;
    for(int i=0;i<size;i++){
        if(P[i]==1){
            black.push(i);//记录黑点的坐标
        }
        else{
            white.push(i);
        }
    }
    //开始配对
    int res=0;
    while(!black.empty()){
        int x=black.top();
        black.pop();
        int y=white.top();
        white.pop();
        res+=abs(x-y);
        n--;
    }
    return res;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int m;
    if (cin >> m) {
        while (m--) {
            int n;
            cin >> n;
            
            // 每组数据有 2n 个点
            vector<int> P(2 * n);
            for (int i = 0; i < 2 * n; i++) {
                cin >> P[i];
            }
            cout << Solution(P) << "\n";
        }
    }
    return 0;
}