#include<iostream>
#include"One_Node.h"
#include <stdexcept>

//初始化
Node::Node() {
	next_ptr = nullptr;
	data = 0;
}
Node::Node(int new_data) {
	data = new_data;
	next_ptr = nullptr;
}

LinkedList::LinkedList(Node* headNode) {
	head = headNode;
	lenth = 1;
}


//头插入法
void LinkedList::insertHead(int next) {
	Node* newNode = new Node(next);
	
	newNode->next_ptr = head;

	lenth++;

	//改变链表的入口
	head = newNode;

}

void LinkedList::showList() {
	Node* temp = head;
	while (temp != nullptr) {
		std::cout << temp->data << std::endl;
		temp = temp->next_ptr;

	}
}

void LinkedList::insertTail(int newData) {
	Node* tail = head;
	Node* newNode = new Node(newData);

	while (tail->next_ptr != nullptr) {
		tail = tail->next_ptr;
	}
	tail->next_ptr = newNode;

}

int LinkedList::findItem(int pos) {
	//从头开始查找
	int count = 1;
	Node* target = head;
	if (pos <= lenth) {
		while (count < pos) {
			target = target->next_ptr;
			count++;
		}
		return target->data;
	}
	else {
		throw std::out_of_range("不存在这个编号的节点");
	}
}

void LinkedList::deletItem(int pos) {
	Node* temp = nullptr;
	int count = 1;
	Node* target = head;
	Node* pre_target = nullptr;
	if (pos <= lenth) {
		while (count < pos) {
			if (count == pos) {
				delete target;
			}
			else {
				target = target->next_ptr;
				count++;
			}
		}
		//找到了目标删除位置的节点

		
	}
	else {
		throw std::out_of_range("不存在这个编号的节点");
	}
	
}

