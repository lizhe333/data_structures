import sys
def getPrecedence(c):
    #获取运算符的优先级
    if c == '+' or c == '-':
        return 1
    if c == '*' or c == '/':
        return 2
    return 0

def infix_to_postfix(expression):
    #创建工作栈

    stack=[]
    postfix=[] #用于储存后缀表达式

    for char in expression:
        #如果操作数是字母

        if 'a'<=char<='z' or 'A'<=char<='Z':
            postfix.append(char)
        #如果是左括号
        #直接入栈
        elif char == '(':
            stack.append(char)
        #如果是有括号
        #则一直弹出，直到匹配为止
        #在python的语法当中[-1]就是获取最后一个元素了
        elif char == ')':
            while stack and stack[-1] != '(':
                postfix.append(stack.pop())
        #当匹配到了左括号
            stack.pop()
        else:
            #如果是其他的运算符，则需要比较
            while stack and getPrecedence(char) <= getPrecedence(stack[-1]):
                #如果新的优先级小于等于z堆栈的优先级，则弹出
                postfix.append(stack.pop())
            stack.append(char)
    #for循环结束以后需要把所有的字符都pop出来
    while stack:
        postfix.append(stack.pop())
        
    return "".join(postfix)
# def main():
#     """主函数，处理输入输出"""
    
#     # 尝试读取 T（测试数据组数）
#     try:
#         T_str = sys.stdin.readline()
#         if not T_str:
#             return  # 如果输入为空，则退出
        
#         T = int(T_str.strip())

#         for _ in range(T):
#             line = sys.stdin.readline().strip()
#             if line:
#                 postfix_result = infix_to_postfix(line)
#                 print(postfix_result)
                
#     except EOFError:
#         pass
#     except Exception as e:
#         # print(f"An error occurred: {e}", file=sys.stderr)
#         pass

# if __name__ == "__main__":
#     main()