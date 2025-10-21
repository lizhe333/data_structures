#pragma once
class String {
private:
	char* str;
	int str_len;
public:
	String(const char* init);
	/*bool operator==(String t);
	bool operator!();*/
	int Length();
	/*String Concat(String t);
	String Substr(int i, int j);*/
	//int Find(String pat);
	int KPM_Find(String pat);
	void ComputeNext(int* array);
	// 获取内部字符串指针（方便打印）
	const char* GetStr() const;
};