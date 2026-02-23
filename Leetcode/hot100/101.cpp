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
//检查一个二叉树是否是镜像对称的。
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        return isMirror(root->left,root->right);
    }
    bool isMirror(TreeNode*p,TreeNode*q){
        //如果两个节点都为空，则它们是镜像对称的
        if(p==nullptr&&q==nullptr){
            return true;
        }
        if(p==nullptr||q==nullptr){
            return false;
        }
        //不存在有空的情况就判断当前节点的值是否相等，并且递归地比较左子树和右子树
        return p->val==q->val&&isMirror(p->left,q->right)&&isMirror(p->right,q->left);
    }
};