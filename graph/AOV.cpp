#include<iostream>
#include<vector>
#include<queue>
#include<stack>
using namespace std;

//拓扑排序的函数
vector<int> topologicalSort(vector<vector<int>>&adj,int v){
    queue<int>q;//用于存放所有入度为0的点
    vector<int>in_dregee(v,0);
    vector<int>res;//存放拓扑排序结果

    //首先遍历邻接表的每个边，计算每个点的入度
    for (int i = 0;i<v;i++){
      for (int j:adj[i]){
        in_dregee[j]++;
      }
    }

    //将所有入度为0的点入队
    for (int i = 0 ;i<v;i++){
      if(in_degree[i]==0){
        q.push(i);
      }
    }
    //开始主循环
    while(!q.empty()){
      //取出队首元素
      int u = q.front();
      q.pop();
      res.push_back(u);//将其加入结果中
      //遍历u的邻接点
  for(int j:adj[u]){
        in_dregee[j]--;
        if(in_degree[j]==0){
          q.push(j);
        }
      }
    }
    //判断是否存在环
    if(res.size()!=v){
      cout<<"图中存在环，无法进行拓扑排序"<<endl;
      return {};
    }
    return res;
}

//课程ppt上的实现方式，使用一个模拟栈的数组实现
vector<int> topologicalOrder(vector<vector<int>>&adj,int v){
  //创建一个存放拓扑排序结果的数组
  vector<int>res(v,-1);
  //创建一个数组来模拟栈结构，既能存放入度，也能存放入度为0的节点
  vector<int>count(v,0);
  int top = -1; //模拟栈顶指针
  //遍历所有的顶点来初始化
  for(int i=0;i<v;i++){
    for(int j:adj[i]){
      count[j]++;
    }
  }

  //将入度为0的入栈
  for(int i = 0;i<v;i++){
    if(count[i]==0){
      count[i] = top;
      top = i;
    }
  }

  //开始主循环,由于要弹出v个节点
  for (int i = 0;i<v;i++){
    //先要检查是否为空
    if(top==-1){
      cout<<"图中存在环，无法进行拓扑排序"<<endl;

      return {};
    
    }
    //首先弹出栈顶的元素
  
  int u = top;
  top = count[top];
  //加入结果数组
  res.push_back(u);
  for (int j:adj[u]){
    count[j]--;
    if(count[j]==0){
      count[j] = top;
      top = j;
    }
  }
}
//判断是否存在环
  if(res.size()!=v){
    cout<<"图中存在环，无法进行拓扑排序"<<endl;
    return {};
  }
  return res;
}
//创建节点
struct Activaty{
  int u;//起始节点
  int v;//结束节点
  int weight;//边的权重
}
class AOVsolution{
  vector<Activaty> findCrticalPath(vector<vector<pair<int,int>>>&adj,int v){
    //adj的结构<点，权重>
    //准备一些必要的数据结构
    vector<int>ve(v,0);//事件最早发生时间
    vector<int>vl(v,INT_MAX);//事件最晚发生时间
    vector<int>in_degree(v,0);//入度数组
    vector<int>topo_order;//拓扑排序结果
    queue<int>q;//用于存放入度为0的节点
    vector<Activaty>criticalPath;//用于存放关键路径上的活动

    //-----------------开始正向的拓扑排序-----------------
    //首先遍历邻接表，计算每个节点的入度
    for(int i = 0;i<v;i++){
      for(auto& edge:adj[i]){
        int point = edge.first;
        in_degree[point]++;
    }
  }
  //将入度为0的节点入队
  for (int i=0;i<v;i++){
    if(in_degree[i]==0){
      q.push(i);
    }
  }
  //开始主循环
  while(!q.empty()){
    //取出队首
    int u = q.front();
    q.pop();
    topo_order.push_back(u);//将其加入拓扑排序结果中
    //遍历u的邻接点
    for (auto& edge:adj[u]){
      int point = edge.first;
      int weight = edge.second;
      if(ve[u]+weight>ve[point]){
        //更新最早开始时间
        ve[point] = ve[u]+weight;
      }
      //更新图
      
    }
  }
  //判断是否有环
  if(topo_order.size()!=v){
    cout<<"图中存在环，无法进行关键路径分析"<<endl;
    return {};
  }

}
}