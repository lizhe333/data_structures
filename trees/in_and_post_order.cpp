#include<iostream>
#include <unordered_map>
#include<vector>
using namespace std;

struct Node {
	int val;
	Node* left;
	Node* right;
	Node(int x) : val(x), left(NULL), right(NULL) {}
};


Node* buildTree(vector<int>& postorder, int post_index, unordered_map<int, int>& inorder_map, int in_left, int in_right) {
	//递归的结束条件
	//中序遍历的左边界大于右边界，则返回NULL
	if (in_left > in_right) {
        return NULL;
    }

	//找到根节点
	int root_val = postorder[post_index];
	//把这个根节点单独创建出来
	Node* root = new Node(root_val);

	int inorder_root_index = inorder_map[root_val];
	int num_right = in_right - inorder_root_index;
	//接下来就是构建左子树和右子树了
	root->left = buildTreeHelper(postorder, post_index-1, inorder_map, in_left, inorder_root_index - 1);
	root->right = buildTreeHelper(postorder, post_index - 1, inorder_map, inorder_root_index + 1, in_right);

	return root;
    
}
