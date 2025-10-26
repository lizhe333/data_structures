#include<iostream>

struct  TreeNode
{
public:
    //定义一个左孩子结点，和一个右孩子结点
	TreeNode* left;
    TreeNode* right;
    int value;
    TreeNode(int value)
    {
        this->value = value;
        this->left = NULL;
        this->right = NULL;
    }
};
//前序遍历
void pre_order(TreeNode* node)
{ 
    if (node == NULL)
        return;
    else {
        std::cout << node->value << std::endl;  //N
        pre_order(node->left); //L
        pre_order(node->right); //N

    }
}

//中序遍历
void in_order(TreeNode* node)
{
    if (node == NULL)
        return;
    else {
        in_order(node->left); //L
        std::cout << node->value << std::endl;  //N
        in_order(node->right); //N
    }
}
void post_order(TreeNode* node)
{
    if (node == NULL)
        return;
    else {
        post_order(node->left); //L
        post_order(node->right); //N
        std::cout << node->value << std::endl;  //N
    }
}
void delete_tree(TreeNode* node)
{
    if (node == NULL)
        return;
    else {
        delete_tree(node->left); //L
        delete_tree(node->right); //N
        delete node;
    }
}

// === 第2步和第5步：主函数 ===
int main() {

    // === 第2步：构建树 ===
    //       'A'
    //      /   \
    //     'B'   'C'
    //    / \     \
    //   'D' 'E'   'F'
    std::cout << "构建树..." << std::endl;
    TreeNode* root = new TreeNode('A');
    root->left = new TreeNode('B');
    root->right = new TreeNode('C');
    root->left->left = new TreeNode('D');
    root->left->right = new TreeNode('E');
    root->right->right = new TreeNode('F');

    // === 第5步：执行遍历 ===
    std::cout << "\n前序遍历 (NLR):" << std::endl;
    pre_order(root);
    // 预期输出: A B D E C F

    std::cout << "\n\n中序遍历 (LNR):" << std::endl;
    in_order(root);
    // 预期输出: D B E A C F

    std::cout << "\n\n后序遍历 (LRN):" << std::endl;
    post_order(root);
    // 预期输出: D E B F C A

    // === 第4步(执行)：清理内存 ===
    std::cout << "\n\n清理树..." << std::endl;
    delete_tree(root);
    root = nullptr; // 好习惯：删除后将指针设为空

    std::cout << "清理完毕。" << std::endl;

    return 0; // 程序正常退出
}