#include<iostream>
#include<vector>

struct Node {
public:
	int val;
	Node* left;
	Node* right;
	Node(int val) {
		this->val = val;
		left = right = NULL;
	}
};

//解决从二叉搜索树当中删除一个节点的问题
Node* findMin(Node* root) {
	//通过查找删除节点的右子树的最小节点
	Node* cur = root->right;
	while (cur->left != NULL){
		cur = cur->left;
	}
	return cur;
}

//从以root为根的二叉搜索树当中删除值为key的节点
Node* deleteNode(Node* root, int key) { 
	//首先找到这个节点
	//如果不是一个有效树
	if (root == NULL) {
		return NULL;
	}
	//递归删除
	if (root->val > key) {
		//这里的赋值是为了把删除的节点的左子树给root的左子树
		root->left = deleteNode(root->left, key);
		//即不光是把节点删除了，还把节点的左子树给root的左子树
	}
	else if (root -> val < key) {
		root->right = deleteNode(root->right, key);
	}
	else {
	//如果真的找到了这个节点
		//此时的root就是要删除的节点
		//case1如果删除的节点没有子节点
		if (root->left == NULL && root->right == NULL) {
		delete root;
		return NULL;
		}
		//如果仅有一个子节点
		if (root->left == NULL || root->right == NULL) {
		Node*child = root->left ? root->left : root->right;
        delete root;
		return child;
		}
		//如果有两个子节点
        Node*min = findMin(root);
        //赋值
		root->val = min->val;
		//从右子树里面递归的删除节点
		root->right = deleteNode(root->right, min->val);
	}
	return root;
}