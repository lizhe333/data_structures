//反转二叉树
#include<iostream>
#include<vector>
using namespace std;

  struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        //递归地进行反转，先反转最小的子树
        if(root==nullptr){
            return nullptr;
        }
        TreeNode* left=invertTree(root->left);
        TreeNode* right=invertTree(root->right);
        //交换左右子树
        root->left=right;
        root->right=left;
        return root;
    }
};