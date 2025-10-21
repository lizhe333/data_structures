//#include<iostream>
//#include<string>
//#include<stack>
//#include<unordered_map>
//
////定义字符串的优先级
//int getPrecedence(char op) {
//	if (op == '+' || op == '-') {
//		return 1;
//	}
//	else if (op == '*' || op == '/') {
//
//		return 2;
//	}
//
//	//( 和其他的字符的优先级都为0
//	//这样就不会因为优先级而把(弹出
//	return 0;
//}
//
////编写中缀表达式转后缀表达式的函数
//std::string infixToPostfix(std::string infix) {
//
//	//创建工作栈
//	std::stack<char> s;
//	std::string postfix;
//	for (char ch : infix) {
//
//		//如果操作符是字母，则直接加入结果字符串
//		if (ch <= 'z' && ch >= 'a') {
//			postfix += ch;
//		}
//		//如果遇到左括号直接入栈
//		else if (ch == '(') {
//			s.push(ch);
//		}
//		else if (ch == ')') {
//			//如果遇到有括号要不断弹出栈中的元素，直到遇到左括号
//			//同时将弹出的元素加入结果字符串
//			while (!s.empty() && s.top() != '(') {
//				postfix += s.top();
//				s.pop();
//			}
//			//现在栈顶的左括号弹出
//			s.pop();
//		}
//		//如果是操作符，则需要判断优先级
//		else {
//			int pos = getPrecedence(ch);
//			while (!s.empty() && getPrecedence(s.top()) >= pos) {
//
//				//高优先级的符号先加入结果字符串
//				//注意：即使是相同优先级的符号，先加入的先加入结果字符串
//				postfix += s.top();
//				s.pop();
//			}
//			s.push(ch);
//		}
//	}
//	//for循环结束后，栈中剩余的元素也要加入结果字符串
//	while (s.empty() == false) {
//		postfix += s.top();
//		s.pop();
//	}
//	return postfix;
//}

//int main() {
//	// 提高C++的IO效率，在OJ中常用
//	std::ios_base::sync_with_stdio(false);
//	std::cin.tie(NULL);
//	std::cout.tie(NULL);
//
//	int T;
//	std::cin >> T;
//	while (T--) {
//		std::string infix_expression;
//		std::cin >> infix_expression;
//		std::string postfix_expression = infixToPostfix(infix_expression);
//		std::cout << postfix_expression << std::endl;
//	}
//	return 0;
//}