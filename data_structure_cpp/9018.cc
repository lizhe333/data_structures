#include<iostream>
#include<vector>
#include<string>
using namespace std;
void getFailureFunction(const string& a ){
  int len = a.length();
  vector<int> failure(len);
  failure[0]=-1;

  //开始遍历字符串
  int j = -1;
  for(int i=1;i<len;i++){
    //i代表当前匹配到的字符
    //首先解决没有匹配的问题
    while(j!=-1&&a[i]!=a[j+1]){
      j=failure[j];
    }
    //当跳出来while循环时，说明要么j==-1，要么a[i]==a[j+1]
    if(a[i]==a[j+1]){
      j++;
    }

    failure[i]=j;

  }
  for (int i = 0; i < len; i++) {
        cout << failure[i];
        if (i < len - 1) cout << " ";
    }
    cout << endl;
}
int main() {
    int T;
    if (cin >> T) {
        string s;
        while (T--) {
            cin >> s;
            getFailureFunction(s);
        }
    }
    return 0;
}