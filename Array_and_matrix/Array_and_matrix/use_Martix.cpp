#include"Martix.h"
#include<iostream>
int main() {
	//初始化8个非0点
	MartixItem* smArray = new MartixItem[8];
	const int terms = 8;
	int initial_data[terms][3] = {

		{0, 1, 12},
		{0, 2, 9},
		{2, 0, -3},
		{2, 5, 14},
		{3, 2, 24},
		{4, 1, 18},
		{5, 0, 15},
		{5, 3, -7}
	};
	for (int i = 0; i < terms; i++) {
		//创造一个临时对象并且复制到smArray[i]上
		smArray[i] = MartixItem(initial_data[i][0], initial_data[i][1], initial_data[i][2]);
	}
	SpareMartix sparemartix(7, 6, terms, smArray);
	sparemartix.print();
	std::cout << "-------------------------开始进行转置————————————" << std::endl;
	SpareMartix normal_sparemartix = sparemartix.Transport();
	normal_sparemartix.print();
	std::cout << "---------------------------开始使用快速排序---------------------" << std::endl;
	SpareMartix fast_sparemartix = sparemartix.FastTranspot();
	fast_sparemartix.print();
}