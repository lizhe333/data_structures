import sys
def getPrecedence(c):
    #获取运算符的优先级
    if c == '+' or c == '-':
        return 1
    if c == '*' or c == '/':
        return 2
    return 0

#构造一个辅助函数用来进行数字和运算
def applyOp(vals,ops):
    """
    辅助函数：执行一次运算
    从 ops 弹出一个操作符, 从 vals 弹出两个数字
    计算结果, 再压回 vals
    """
    op = ops.pop()
    val2 = vals.pop()
    val1 = vals.pop()
    
    #注意这里的运算是vals1 abs val2
    if op == '+':
        vals.append(val1 + val2)
    elif op == '-':
        vals.append(val1 - val2)
    elif op == '*':
        vals.append(val1 * val2)
    elif op == '/':
        vals.append(int(val1 / val2))

def evaluate(expression):
    ops =[]
    vals = []
    
    i = 0
    while i < len(expression):
        c = expression[i]
        
        #当获取到的是数字
        if c.isdigit():
            num_str=''
            while i < len(expression) and expression[i].isdigit():
                num_str += expression[i]
                i += 1
            vals.append(int(num_str))
            i -= 1
        elif c=='(':
            ops.append(c)
        elif c==')':
            while ops[-1]!='(' and ops:
                applyOp(vals,ops)
            ops.pop()
        elif c in ['+', '-', '*', '/']:
            while ops and getPrecedence(c) <= getPrecedence(ops[-1]):
                applyOp(vals,ops)
            ops.append(c)
            
        elif c=='#':
           while ops:
                applyOp(vals,ops)
           break
        i+= 1
    return vals.pop()
            
# def main():
#     """主函数，处理输入输出"""
#     try:
#         T_str = sys.stdin.readline()
#         if not T_str:
#             return  # 如果输入为空，则退出
        
#         T = int(T_str.strip())

#         for _ in range(T):
#             line = sys.stdin.readline().strip() # 读取一行并去掉换行符
#             if line:
#                 result = evaluate(line)
#                 print(result)
                
#     except EOFError:
#         pass
#     except Exception as e:
#         # 在OJ中，最好不要打印任何多余信息
#         # print(f"An error occurred: {e}", file=sys.stderr)
#         pass

# if __name__ == "__main__":
#     main()