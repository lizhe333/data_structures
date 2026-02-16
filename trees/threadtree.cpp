struct threadtreenode
{
    int value;
    threadtreenode* left, *right;
    bool lflag, rflag;
};
void InThread(threadtreenode* &p, threadtreenode* &pre){
    //pre是在递归过程中记录上一个是谁
    if(p!=nullptr){
        //递归线索化左子树，一直向左边走，走到最左边
        InThread(p->left, pre);

        //如果p没有左孩子，就把p的左指针指向前驱节点
        if(p->left==nullptr){
            p->left = pre;
            p->lflag = true;
        }
        
        //处理上一个节点pre的后继线索，属于回头的操作
        //此时的p是pre的后继，如果pre没有右孩子，则将pre的右指针指向p
        if(pre!=nullptr && pre->right==nullptr){
            pre->right = p;
            pre->rflag = true;
        }
        //更新当前节点
        pre = p;
        InThread(p->right, pre);
    }
}
