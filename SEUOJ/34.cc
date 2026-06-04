#include<iostream>
#include<vector>
#include<iomanip>
using namespace std;
int main(){
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);
    vector<double>res;
    int T;
    
    cin>>T;
    while(T>0){
        int n=0;//岛屿数
        cin>>n;
        int bridge=n-1;//初始化桥的个数
        
        double temp=1.0;
        while(bridge){
            bridge--;
            int a=0;
            cin>>a;
            temp+=a/100.0;
        }
        res.push_back(temp);
        T--;
    }
    for (int i = 0; i < res.size(); i++) {
            cout << fixed << setprecision(6) << res[i] << "\n";
        }
    return 0;

}