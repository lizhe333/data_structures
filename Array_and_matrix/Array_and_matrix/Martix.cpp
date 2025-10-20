#include"Martix.h"
#include<iostream>
MartixItem::MartixItem() {
	row = 0;
	column = 0;
	value = 0;
}
MartixItem::MartixItem(int a, int b, int c) {
	row = a;
	column = b;
	value = c;
}
SpareMartix::SpareMartix(int column,int row,int value,int capictiy) {
	row_number = row;
	column_number = column;
	terms = value;
	smArray = new MartixItem[value];
	capasity = row * column;
}
SpareMartix::SpareMartix(int column, int row , int value, MartixItem*a) {
	row_number = row;
	column_number = column;
	terms = value;
	smArray = a;
	capasity = row * column;

}
void SpareMartix::print() {
	std::cout << "这个矩阵有" << row_number << "行" << column_number << "列" << terms << "个非零值" << std::endl;
	for (int i = 0; i < terms; i++) {
		//对指针使用[i]运算符会直接返回一个对象，而非指向这个对象的指针
		std::cout << "第" << i + 1 << "个有数字的地方" << "坐标是(" << smArray[i].row
			<< "," << smArray[i].column << "),这里的值是" << smArray[i].value<<std::endl;
	}

}

SpareMartix SpareMartix::Transport() {
	SpareMartix temp(this->row_number, this->column_number, this->terms,this->capasity);
	int index = 0;
	
	for (int i = 0; i < column_number; i++) {
		//扫描smArray中的每一个有数字的位置
		for (int j = 0; j < terms; j++) {
			//找到了存在数字的列
			if (smArray[j].column == i) {
//smArray[index]是新元素该在新数组当中的位置
				//由于行数本身也是从小到大所以转置之后，到相应的列，自然也是从小到大排布
				temp.smArray[index].column = smArray[j].row;
				temp.smArray[index].row = smArray[j].column;
				temp.smArray[index].value = smArray[j].value;
				index++;
			}

		}
	}
	return temp;
	std::cout << "转置完成" << std::endl;
}

SpareMartix SpareMartix::FastTranspot() {
	SpareMartix temp(this->row_number, this->column_number, this->terms, this->capasity);
	//int* row_size = new int[row_number]();这是错误代码，应该是列数个一维数组
	int* row_size = new int[column_number]();
	for (int i = 0; i < terms; i++) {
		
		//遍历存在数字的每一个位置
		//在所在的行上面加一
		int index = smArray[i].column;
		row_size[index]++;
	}
	//创建一个row_start的新一维数组
		int* row_start = new int[row_number]();
	for (int i = 1; i < row_number; i++) {
		//错误代码row_start[i] += row_size[i];
		
		row_start[i] = row_start[i - 1] + row_size[i - 1];
	}
	//开始进行转置
	for (int i = 0; i < terms; i++) {
	
		//由于转置之后的行跟列也要按照
		//从小到大的顺序进行排列
		//所以先扫描列（在同一个行的基础上，因为被row_start限制住了）
		//由于原本在一个行的数字，转置之后在同一列上，
		// 所以自然可以保证同一列上面的大小顺序
		int row_index = row_start[smArray[i].column];
		temp.smArray[row_index].column = smArray[i].row;
		temp.smArray[row_index].row = smArray[i].column;
		temp.smArray[row_index].value = smArray[i].value;
		row_start[smArray[i].column]++;
	}
	return temp;
}
//// 假设这是 SpareMartix 类的一个成员函数
//SpareMartix SpareMartix::FastTranspot() {
//	// 1. 【修正】创建尺寸正确的新矩阵 T，行列数与原矩阵相反
//	SpareMartix T(this->column_number, this->row_number, this->terms,capasity);
//
//	if (this->terms > 0) {
//		// 2. 【修正】辅助数组的大小应为原矩阵的列数
//		int* num = new int[this->column_number]();
//		int* cpot = new int[this->column_number]();
//
//		// 3. 【修正】统计原矩阵中“每一列”的非零元个数
//		for (int i = 0; i < this->terms; ++i) {
//			num[this->smArray[i].column]++;
//		}
//
//		// 4. 计算每一列在新矩阵T中的起始位置（您的这部分逻辑已基本正确）
//		cpot[0] = 0;
//		for (int col = 1; col < this->column_number; ++col) {
//			cpot[col] = cpot[col - 1] + num[col - 1];
//		}
//
//		// 5. 执行转置（您最后的循环逻辑是正确的！）
//		for (int p = 0; p < this->terms; ++p) {
//			int col = this->smArray[p].column;
//			int q = cpot[col];
//
//			T.smArray[q].row = this->smArray[p].column;
//			T.smArray[q].column = this->smArray[p].row;
//			T.smArray[q].value = this->smArray[p].value;
//
//			cpot[col]++; // 为该列的下一个元素准备位置
//		}
//
//		// 释放临时申请的内存
//		delete[] num;
//		delete[] cpot;
//	}
//
//	std::cout << "快速转置完成" << std::endl;
//	return T;
//}