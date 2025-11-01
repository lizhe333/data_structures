//利用二叉树的层序遍历和中序遍历实现树的构造

#include<iostream>
#include<queue>
#include<vector>
#include<unordered_map>

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode* buildTree(vector<int>& levelorder, unordered_map<int, int >& inorder_map, int in_left, int in_right) {
	if (in_left > in_right) {
		return NULL;
	}

	TreeNode* root = NULL;
	int inorder_root_index= -1; //就是设置一个哨兵值，避免in_left > in_right

	for (int root_val : lelevelorder) {
	//按顺序遍历levelorder，找到根节点的值
		int current_index = inorder_map[root_val];
		//判断这个值是不是在处理范围之内
        if (current_index >= in_left && current_index <= in_right) { 
			root = new TreeNode(root_val);
            inorder_root_index = current_index;
            break;
		}
		root->left = buildTree(levelorder, inorder_map, in_left, inorder_root_index - 1);
        root->right = buildTree(levelorder, inorder_map, inorder_root_index + 1, in_right);
		return root;

	}
}