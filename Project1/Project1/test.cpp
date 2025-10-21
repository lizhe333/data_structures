#include<iostream>
#include"One_Node.h"
int main() {

	//创建三个实例节点
	Node* head1 = new Node(1);
	LinkedList list1(head1);
	list1.insertHead(3);
	list1.insertHead(2);
	std::cout << "使用头添加，添加顺序是3,2，最终的输出是" << std::endl;
	list1.showList();
	std::cout << "如果使用尾添加：" << std::endl;
	Node* head2 = new Node(1);
	LinkedList list2(head2);
	list2.insertTail(3);
	list2.insertTail(2);
	list2.showList();

	list1.insertHead(4);
	list1.insertTail(5);
	list1.insertHead(6);
	std::cout << "现在添加后的链表是：" << std::endl;
	list1.showList();
	std::cout << "-----------------开始测试查找第3个节点的数据------------------------" << std::endl;
	std::cout << list1.findItem(3) << std::endl;
	std::cout << "---------------------开始测试超出列表范围的数据----------------------" << std::endl;
	try {
		// 故意调用一个会出错的函数
		std::cout << "正在尝试访问一个不存在的位置..." << std::endl;
		list1.findItem(99); // 这一行会 throw

	}
	// 用 catch 块来捕获特定类型的异常
	catch (const std::out_of_range& e) {
		// 如果捕获成功，这里的代码就会执行
		// 这时你就会在控制台看到输出了！
		std::cerr << "成功捕获到异常! 错误信息: " << e.what() << std::endl;
	}


}