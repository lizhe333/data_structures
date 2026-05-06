//大整数乘法
#include<iostream>
#include<cmath>
#include <algorithm>
#include <string>
#include<vector>
using namespace std;

//去除字符串前导0
string RemoveZeros(string str){
    for(int i=0;i<str.size();i++){
        if(str[i]!='0'){
            return str.substr(i);
        }
    }
    return "0";
}

//模拟string的大整数加法
string add(string a,string b){
    //两个指针，分别指向两个加数
    int i = a.size()-1;
    int j = b.size()-1;
    string res="";
    int carry=0;
    while(i>=0||j>=0||carry){
        int sum=carry;
        if(i>=0){
            sum+=a[i]-'0';
            i--;
        }
        if(j>=0){
            sum+=b[j]-'0';
            j--;
        }
        //本位应该保存的结果
        res+=to_string(sum%10);
        //进位
        carry=sum/10;
    }
    //最后要反转整个结果
    reverse(res.begin(),res.end());
    return res;
}

//模拟string的大整数减法
string Subtract(string a,string b){
    int i = a.size()-1;
    int j = b.size()-1;
    string res="";
    int borrow=0;
    //只要前面的这个数字还没有减完(因为它最长)
    while(i>=0){
        int diff=a[i]-'0'-borrow;
        if(j>=0){
            diff-=b[j]-'0';
            j--;
        }
        //如果不够，借位
        if(diff<0){
            diff+=10;
            borrow=1;
        }else{
            borrow=0;
        }
        res+=to_string(diff);
        i--;
    }
    reverse(res.begin(),res.end());
    return RemoveZeros(res);
}

//一个工具函数，将字符串补齐长度，补零
void PadZeros(string &num1,string &num2){
    int len1=num1.size();
    int len2=num2.size();
    int len=max(len1,len2);
    if(len1<len){
        num1=string(len-len1,'0')+num1;
    }else if(len2<len){
        num2=string(len-len2,'0')+num2;
    }
}

//开始模拟string的大整数乘法
string Karatsuba(string a,string b){
        PadZeros(a,b);
        int n=a.size();
        //当长度小于4个，直接转换成longlong开始计算
        if(n<=4){
            long long res=stoll(a)*stoll(b);
            return to_string(res);
        }
        //按位数拆分成高位和低位
        int m=n/2;
        int m_actual=n-m;

        string a_high=a.substr(0,m_actual); 
        string a_low=a.substr(m_actual);
        string b_high=b.substr(0,m_actual);
        string b_low=b.substr(m_actual);
        string z0=Karatsuba(a_low,b_low);
        string z2=Karatsuba(a_high,b_high);
        string z1_temp=Karatsuba(add(a_high,a_low),add(b_high,b_low));

        string z1=Subtract(Subtract(z1_temp,z2),z0);
        //最后的结果是z2*10^(2*m)+z1*10^m+z0
        string term2=z2+string(2*m,'0');
        string term1=z1+string(m,'0');
        return RemoveZeros(add(add(term2,term1),z0));

}

int main() {

    string x, y;
    if (cin >> x >> y) {
        cout << Karatsuba(x, y) << "\n";
    }
    return 0;
}





// long long Powlong(int exp){
//     long long rel=1;
//     long long base =10;
//     while(exp>0){
//         if(exp%2==1){
//             rel=rel*base;
//         }
//         base=base*base;
//         exp=exp/2;
//         }
//     return rel;
// };
// long long Karatsuba(long long x,long long y){
//     //基础情况
//     if(x<=10||y<=10){
//         return x*y;
//     }
//     int n=max((int)log10(x)+1,(int)log10(y)+1);
//     int m=n/2;
//     long long  power=Powlong(m);
//     long long  a=x/power;
//     long long  b=x%power;
//     long long  c=y/power;
//     long long  d=y%power;
//     long long z0=Karatsuba(a,c);
//     long long z1=Karatsuba(b,d);
//     long long z2=Karatsuba(a+b,c+d)-z0-z1;
//     return z2*Powlong(2*m)+z1*Powlong(m)+z0;
// }
// int main(){
//     long long a;
//     long long b;
//     cin>>a>>b;
//     cout<<Karatsuba(a,b)<<endl;
// }
