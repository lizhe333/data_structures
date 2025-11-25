#include <iostream>
#include <utility>
//创造一种墓碑地址，独立于有效地址，与空地址之间
template<class K,class E>
class LinearProbing{
  private:
  int b; //表的容量
  pair<K,E>* *ht; //存放指针的数组
  int h(const K&k){ return (int)k%b;} //散列函数
  public:
  LinearProbing(int capacity){
    b=capacity;
    ht = new pair<K,E>*[b];//一共有b个桶
    for (int i =0;i<b;i++){
      //初始化每个桶的地址为空
      ht[i]=nullptr;
    }

    pair<K,E>* Get(const K&k);
    void Delete(const K&k);
  }
}
templete<class K,class E>
static LinearProbinng::pair<K,E>*deleteSlot=(pair<K,E>*)1;
//强行将1这个整数地址转换成pair<K,E>*类型的指针地址
//是一个假指针
templete<class K,class E>
void LinearProbing<K,E>::Delete(const K&k){
  //首先找到元素
  int i = h(k);
  int j = i;
  while(ht[j]!=nullptr){
    if(ht[j]!=deleteSlot&&ht[j]->first==k){
      //找到了目标元素
      delete ht[j];//释放这个元素所占用的内存
      ht[j]=deleteSlot; //将这个地址标记为墓碑地址
      return ;
    }
    //没有找到的话就继续向下，但是为了能回头，所以要对b取模
    j=(j+1)%b;

    if(j==i){
      //说明没有找到找了一圈了又回来了
      return ;
    }

  }
}
template<class K,class E>
pair<K,E>* LinearProbing<K,E>::Get(const K&k){
  //首先找到这个元素
  int i = h(k);
  int j = i;
  while(ht[j]!=nullptr){
    if(ht[j]!=deleteSlot&&ht[j]->first==k){
      return ht[j];
    }
    j=(j+1)%b;
    if(j==i){
      return nullptr;
    }
  }

}