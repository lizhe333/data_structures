#include"String.h"
#include<cstring>
String::String(const char* init) {
	
	if (init == nullptr) {
		str_len = 0;
		str = new char[1];
		str[0] = '\0';
	}
	else {
		str_len = strlen(init);
		str = new char[str_len + 1];
		strcpy_s(str, str_len + 1, init);
	}


}
int String::Length() {
	return strlen(str);

}
//int String::Find(String pat) {
//	int lengthL = Length();
//	int lengthS = pat.Length();
//	
//	//外层循环遍历所有可能的开始位置
//	for (int i = 0; i < lengthL-lengthS; i++) {
//		int flag = 1;
//		for (int j = 0; j < lengthS; j++) {
//			if (pat.str[j] != str[i + j]) {
//				flag = 0;
//				//这一次的匹配失败，跳出
//				break;
//			}
//			
//		}
//	}
//
//}

int String::KPM_Find(String pat) {
	if (pat.str_len == 0)
		return -1;
	if(pat.str_len>=this->Length())
		return -1;
	int PosP = 0;
	int PosT = 0;
	//next数组保存的是模式串中每个字符前缀和后缀的最大匹配长度
	int* next = new int[pat.Length()+1];
	pat.ComputeNext(next);
	while((PosP<pat.Length())&&(PosT<this->Length())){
		if (pat.str[PosP] == str[PosT])
		{
			PosP++;
			PosT++;
		}
		else if (PosP == 0) {
			//即如果模式串的第一个字符就和当前字符不匹配，那么模式串向后移动一位
			//模式串向后移动，动的是主串的指针
			PosT++;
		}
		else {
			//如果某一个位置上匹配失败了
			//那么需要匹配的是模式串的位置就是next数组中保存的匹配长度
			PosP = next[PosP];
		}
	}
	delete [] next;
	if(PosP<pat.Length())
		return -1;
	else
		return PosT - PosP;

}

void String::ComputeNext(int* next) {
	int Length = this->Length();
	//用来作为移出头的标志
	next[0] = -1;
	int i = 0;//用来遍历模式串
	int k = -1;//用来保存前缀和后缀的最大匹配长度
	while (i < Length) {
		if (k == -1 || str[k] == str[i]) {
			//如果最长匹配子串的后一位与当前字符相同，那么最长匹配子串的长度加1
			i++;
			k++;
			next[i] = k;
		}
		else {
			//如果最长匹配子串的后一位与当前字符不同，那么最长匹配子串的长度减1
			k = next[k];
		}
	}
}
const char* String::GetStr() const {
	return str;
}