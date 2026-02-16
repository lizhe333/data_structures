#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
struct Node
{
    int son;
    int bro;
};
const int MAXN = 100005; 
Node tree[MAXN]; // 静态数组存储树
void solve(){
    int n;
    cin>>n;
    //读取并且构建树
    for(int i =0;i<n;i++){

        int id ,s,b;
        cin>>id>>s>>b;
        tree[id].bro=b;
        tree[id].son=s;
    }
    //遍历树来找最大度
    int max_degree = 0;
    for(int i =1;i<=n;i++){
          int son = tree[i].son;
                if(son==-1){
            continue;
        }
      
        int bro = tree[son].bro;

        int current_degree = 1;
        while(bro != -1){
            current_degree++;
            bro = tree[bro].bro;
        }
        max_degree = max(max_degree,current_degree);
    }
    cout<<max_degree<<endl;
}
int main(){
    // IO 加速
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    if (cin >> T) {
        while (T--) {
            solve();
        }
    }
    return 0;
}
