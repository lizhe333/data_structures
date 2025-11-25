#include<iostream>
#include<vector>
#include<cstddef>
template<class E,class K> class AVLTree;
template<class E,class K>
class AVLNode{
  friend class AVLTree<E,K>;
private:
  E element;
  K key;
  AVLNode<E,K>* leftChild,*rightChild;
  int bf; //平衡因子
  public:
  AVLNode(const E& ele,const K& k):emelent(ele),key(k),leftChild(NULL),rightChild(NULL),bf(0){}
}
template<class E,class K>
class AVLTree{
  public:
  AVLTree():root(NULL){};
  E& find(const K& k);
  void insert(const E& ele,const K& k);
  void Delete(const K& k);
  private:
  AVLNode<E,K>* root;
}
void AVLTree<E,K>::insert(const E& ele,const K& k){
  //首先判断是不是空树
  if(!root){
    root = new AVLNode<E,K>(ele,k);
    return;
  }
  AVLNode<E,K>*p=root;//跟随当前查找的位置
  AVLNode<E,K>*a=root;//记录离当前插入节点最近的一个bf=+1或-1的节点
  AVLNode<E,K>*pp=NULL;//记录p的父节点
  AVLNode<E,K>*pa=NULL;//记录a的父节点

  //寻找插入位置
  while(p){
    //虽然还没有找到该插入的位置，但是持续更新a和pa
    //直到有一天找到了p该放的位置，这样一直更新的a和pa就是离插入节点最近的bf=+1或-1的节点
    if(p->bf!=0){
      //找到了一个新的不为0的节点
      //更新a和pa
      a = p;
      pa = pp;
    }

    //然后再来判断是不是该继续往下找
    if(p->key>k){
      //向左边找
      pp = p;
      p=p->leftChild;
    }
    else if(p->key<k){
      pp=p;
      p=p->rightChild;
    }
    else{
      //已经存在该节点
      p->element = ele;
      return;
    }
  }
AVLNode<E,K>* newNode = new AVLNode<E,K>(ele,k);
  //执行插入新节点，此时p是空，pp是新节点的父节点
  if(pp->key>k){
  //应该成为左孩子
    pp->leftChild = newNode;
  }
  else{
    pp->rightChild = newNode;
  }

  //创建一个待篡位指针
  AVLNode<E,K>*b=NULL;
  int d=0; //记录新插入节点是a的左子树还是右子树
  //第三步，修改a到新节点路径上的BF值
  //首先是记录新插入节点是左边or右边
  if(k>a->key){
    b=p=a->rightChild;
    d=-1;
  }
  else{
    b=p=a->leftChild;
    d=1;
  }

  //这一阶段的p再次从a的孩子节点开始走到新插入节点
  //来更新一路上的bf值
  while(p!=newNode){
    if(k>p->key){
      p->bf=-1;
      p=p->rightChild;
  }
  else {
    p->bf=1;
    p=p->leftChild;
  }

}
//第四步，检查a的bf值
if(!(a->bf)||!(a->bf+d)){
  a->bf+=d;
  return;
  //这部分是新添加的中和了原先的a的一个bf值
}
//如果没有中和，则a就不平衡
if(d==1){
  //左侧变重
if(b->bf==1){
  //则是左边重，说明是LL型
  //进行右旋转
  //首先把子树的右孩子过继给父节点
  a->leftChild = b->rightChild;
  //然后把a拉下来
  b->rightChild = a;
  //更新bf
  a->bf=0;
  b->bf=0;
}
else{
//执行LR型
//先定义一个孙子节点
AVLNode<E,K>*c = b->rightChild;

//把孙子节点的左孩子过继给父节点
b->rightChild = c->leftChild;
c->leftChild = b;

//现在变成LL型
//对a进行旋转
a->leftChild = c->rightChild;
c->rightChild = a;

//关键：计算新的bf值
switch(c->bf){
  case 1:
    a->bf= -1;
    b->bf=0;
    break;
  case 0:
    a->bf=0;
    b->bf=0;
    break;
  case -1:
    a->bf=0;
    b->bf=1;
    break;
  default:
    break;
}
//更新新的根的bf值
c->bf=0;
b=c;
}

//现在旋转完毕，同时不平衡点的子节点也重新指向了新的根节点
if(!pa){
  //说明a是根节点
  root = b;
}
else{
  //说明a不是根节点
  if(pa->leftChild==a){
    pa->leftChild = b;
  }
  else{
    pa->rightChild = b;
}
}
}
}

