#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int Solution(vector<int> w,int c){
//w是货物数组，c是船的载重量
//先对货物数组进行排序
sort(w.begin(),w.end());
int res=0;
int total_weight=0;
while(res<w.size()&&total_weight+w[res]<=c){
    total_weight+=w[res];
    res++;
    
}
return res;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, c;
    while (cin >> n >> c) {
        vector<int> w(n);
        for (int i = 0; i < n; ++i) {
            cin >> w[i];
        }
        cout << Solution(w, c) << "\n";
    }return 0;
}