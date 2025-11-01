import sys
sys.setrecursionlimit(2000)
def solution(preorder, inorder_map,pre_start,pre_end,in_start,in_end):
    
    #如果是范围无效，直接返回
    if pre_start > pre_end or in_start > in_end:
        return None
    
    root = preorder[pre_start]
    root_index = inorder_map[root]
    
    #计算左子树的大小
    left_size = root_index - in_start
    
    #先处理左边，在处理右边
    solution(preorder,inorder_map,pre_start+1,pre_start+left_size,in_start,root_index-1)  
    
    solution(preorder,inorder_map,pre_start+1+left_size,pre_end,root_index+1,in_end)  
    
    print(root,end=" ")
    # 1. 读取测试数据组数 n
try:
    n = int(input())
except EOFError:
    n = 0

# 2. 循环 n 次
for _ in range(n):
    # 3. 读取前序遍历
    #   input().split() -> ['7', '1', '2', '4', '5', '3', '6', '7'] (列表, 元素是字符串)
    pre_line = input().split()
    
    #   pre_line[0] 是节点数 'k'
    k = int(pre_line[0]) 
    
    #   pre_line[1:] 是 'k' 之后的所有元素
    #   [int(x) for x in ...] 是一个列表推导式，把所有字符串转为整数
    preorder = [int(x) for x in pre_line[1:]]

    # 4. 读取中序遍历
    in_line = input().split()
    inorder = [int(x) for x in in_line[1:]]
    
    # 5. 构建优化用的“字典” (map)
    #   enumerate(inorder) 会产生 (索引, 值) 对，例如 (0, 'D'), (1, 'B'), ...
    #   {val: i ...} 是一个字典推导式
    #   键(Key)是节点值(val)，值(Value)是索引(i)
    inorder_map = {val: i for i, val in enumerate(inorder)}

    # 6. 调用递归函数，处理整棵树
    solution(preorder, inorder_map, 0, k - 1, 0, k - 1)

    # 7. 在该组测试数据全部输出后，打印一个换行符
    print()