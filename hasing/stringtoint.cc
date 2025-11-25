#include<iostream>
#include<string>
using namespace std;
unsigned int stringToint(const string& s){
  unsigned int hash = 0;
  int length= (int)s.length();
  if(length%2==1){
    hash+=s.at(length-1);
    length--;
  }
  //按照每两个一组来遍历这个字符串
  for (int i = 0 ;i<length;i+=2){
    //第一个字符直接加
    //第二个字符左移8位再加
    hash+=s.at(i);
    hash+=((int)s.at(i+1)<<8);
  }
  return hash;
}