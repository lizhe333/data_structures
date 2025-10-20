#pragma once
class SpareMartix;
class MartixItem {
	friend SpareMartix;
private :
	int row, column, value;
public:
	MartixItem();
	MartixItem(int , int, int);

};
class SpareMartix {
private:
	int row_number, column_number, terms, capasity;
	
	//这个smArray是一个指向MartixItem的指针，但是后续给他动态的分配一个内存地址
	//来存放一系列的MartixItem对象，他就是一个首地址的作用
	MartixItem* smArray;
public:
	SpareMartix(int, int, int, int capiticty);
	SpareMartix(int, int, int, MartixItem* );
	SpareMartix Transport();
	SpareMartix FastTranspot();
	void print();
};