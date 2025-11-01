//给定二叉树的前序遍历和中序遍历的节点序列，请输出该二叉树的后序遍历节点序列.
//输入第一行是一个int型整数n, 表示后面有n组测试数据.每组数据包含2行，
//第1行第1个数字为二叉树中节点数k，后面是前序遍历的k个节点号序列;
//第2行第1个数字为二叉树中节点数k，后面是中序遍历的k个节点号序列.
//输出n行, 每行为对应二叉树的后序遍历节点序列.

//前序 N,L,R
//中序 L,N,R
//后序 L,R,N

#include <iostream>
#include <vector>
#include<map>

using namespace std;

//map的结构相当于字典
//优点是查找速度快
void Solution(const vector<int>& pre, const map<int, int >& inorder_map,
	int pre_start, int pre_end, int in_start, int in_end) {
		//如果范围无效，则是空树
    if (pre_start > pre_end || in_start > in_end) {
        return;
    }

    //前序遍历的第一个节点是根节点
    int root_val=pre[pre_start];

    //分割大的左子树和右子树
    //使用map查找中序遍历的根节点位置
    int in_root_index = inorder_map.at(root_val);

    //计算左子树的节点数
    int left_size = in_root_index - in_start;

    //递归并且输出(LRN)
    //递归处理左子树
    Solution(pre, inorder_map, pre_start + 1, pre_start + left_size, in_start, in_root_index - 1);
    Solution(pre, inorder_map, pre_start + left_size + 1, pre_end, in_root_index + 1, in_end);
    //输出根节点
    cout<<root_val<<" ";


}
//int main() {
//    int n; // n 组测试数据
//    cin >> n;
//
//    while (n--) {
//        int k; // k 个节点
//        cin >> k; // 读取第 1 行的 k
//
//        // 存储前序遍历序列
//        vector<int> pre_order(k);
//        for (int i = 0; i < k; ++i) {
//            cin >> pre_order[i];
//        }
//
//        // ----------------- 修复点 -----------------
//        int k_ignored; // 定义一个临时变量
//        cin >> k_ignored; // 读取并忽略第 2 行的 k
//        // ------------------------------------------
//
//        // 存储中序遍历序列，并同时构建优化用的 map
//        // 注意：这里我们仍然使用第 1 行读到的 k 来确定大小
//        vector<int> in_order(k);
//        map<int, int> in_order_map;
//        for (int i = 0; i < k; ++i) {
//            cin >> in_order[i];
//            in_order_map[in_order[i]] = i; // 键: 节点值, 值: 索引
//        }
//
//        // 调用递归函数，处理整棵树
//        // 初始范围是 [0, k-1]
//        Solution(pre_order, in_order_map, 0, k - 1, 0, k - 1);
//
//        // 每组测试数据输出后换行
//        cout << endl;
//    }
//
//    return 0;
//}