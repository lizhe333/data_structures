#include<iostream>
#include<vector>
#include<string>
using namespace std;
void getNext(string &a ){
  //首先确定结束的长度
  int len = a.length();
  int j=0;//当前匹配的位置
  int k=-1;//最长前后缀的长度-1，同时代表了从开头来，最大前缀字符串的最后一个字符的下一个字符的位置
  vector<int> next(len);
  next[0]=-1;
  while(j<len-1){
    if(k==-1||a[j]==a[k]){
      //如果新的纳入的一个字符与前面的字符串的最后一个字符匹配
      //则说明前后缀可以继续变长
      j++;
      k++;
      //记录下当前的最长前后缀长度
      next[j]=k;
    }
    else{
      //如果不匹配，则回溯
      //即找最前面匹配字符串的再细分的字符串
      k=next[k];
    }
  }
  for (int i = 0; i < len; i++) {
        cout << next[i];
        if (i < len - 1) {
            cout << " ";
        }
    }
    cout << endl;
}
int main() {
    int n;
    // 读取测试用例数量
    if (cin >> n) {
        string s;
        while (n--) {
            cin >> s;
            getNext(s);
        }
    }
    return 0;
}