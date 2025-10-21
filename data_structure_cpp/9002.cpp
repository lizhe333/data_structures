////和上一题的不同
////这里是处理数字
////需要使用Dijkstra的双栈算法
////算法思路：一个栈用来放数字，一个栈用来放符号
//#include <stack>
//#include <iostream>
//#include<string>
//#include <cctype> //为了使用isdigit()来判断是不是数字'
//using namespace std;
//int getPrecedence(char op)
//{
//	//和上面一题这个部分一样
//	if (op == '+' || op == '-') {
//		return 1;
//	}
//	if (op == '*' || op == '/') {
//		return 2;
//	}
//	return 0; // '(' 和其他字符
//}
//
////创建一个辅助函数，用来处理一次运算
//void applyOp(std::stack<long long >& values, std::stack<char>& ops) {
//
//	//获取栈顶的运算符
//	char op = ops.top();
//	ops.pop();
//
//	//获取栈顶的数字
//	long long b = values.top();
//	values.pop();
//	long long a = values.top();
//	values.pop();
//
//	//需要注意的是运算顺序是 a ops b
//	switch (op) {
//	case '+':
//		values.push(a + b);
//		break;
//	case '-':
//		values.push(a - b);
//		break;
//	case '*':
//		values.push(a * b);
//		break;
//	case '/':
//		values.push(a / b);
//		break;
//	}
//
//
//}
//
////主计算函数
//
//long long evaluate(string expression) {
//	std::stack<long long>vals;
//	std::stack<char>ops;
//
//	for (int i = 0; i < expression.size(); i++) {
//		char c = expression[i];
//
//		//如果遇到数字，还需判断要把数字连接起来处理
//		if (isdigit(c)) {
//			long long num = 0;
//			while (i < expression.size() && isdigit(expression[i])) {
//				//就是发现当前的数字后面还有数字，首先是肯定要变大10倍
//				//然后就是把数字加上
//				num = num * 10 + expression[i] - '0';
//				i++;
//			}
//			vals.push(num);
//			//注意这里循环会+1
//			i--;//所以要-1
//		}
//
//		//处理字符
//		else if (c == '(') {
//			//左括号，直接入栈
//			ops.push(c);
//		}
//		else if (c == ')') {
//			while (!ops.empty() && ops.top() != '(') {
//				applyOp(vals, ops);
//				
//			}
//			ops.pop();
//		}
//		else if (c == '+' || c == '-' || c == '*' || c == '/') {
//			while (!ops.empty() && getPrecedence(ops.top()) >= getPrecedence(c)) {
//			applyOp(vals, ops);
//           
//			}
//			ops.push(c);
//		}
//		else if (c == '#') {
//			//遇到#，就计算所有运算符
//			while (!ops.empty()) {
//				applyOp(vals, ops);
//			}
//			break;
//		}
//	}
//	return vals.top();
//}
//int main() {
//	std::ios_base::sync_with_stdio(false);
//	std::cin.tie(NULL);
//	std::cout.tie(NULL);
//
//	int T;
//	std::cin >> T;
//	while (T--) {
//		std::string expression;
//		std::cin >> expression;
//		std::cout << evaluate(expression) << std::endl;
//	}
//	return 0;
//}