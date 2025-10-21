#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<stdexcept>
template<typename T ,int MAX_SIZE=100>
class Stack {
private:
	T data[MAX_SIZE];
	int top;
public:
	Stack() :top(-1) {}
	void push(const T& value) {
		//处理异常栈满
		if (top >= MAX_SIZE - 1) {
			//现在栈顶的最后一个元素，即栈顶元素的下一个元素
			throw std::overflow_error("栈满");

		}
		else {
			top++;
			data[top] = value;
		}

	}
	void pop() {
		if (isEmpty()) {
			throw std::underflow_error("栈空，无法继续弹出");
		}
		top--;
	}
	bool isEmpty() const {
		return top == -1;
	}
	T& gettop() {
		if (isEmpty()) {
			throw std::underflow_error("栈空");
	}
		return data[top];
	}
	int size() const {
		return top+1;
	}
};

