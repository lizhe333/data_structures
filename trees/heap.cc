void MaxHeap::Push(int x){
    //首先判断是否满了
    if(heapSize==capacity){
        //扩容的代码
    }
    int currentNode = ++heapSize;
    //两个上浮终止条件，要么是根节点，要么是父节点的值比当前节点小
    while(currentNode!=1 && heap[currentNode/2]<x){
        //父节点下移,注意是直接把里面的值给覆盖率，而不是交换
        heap[currentNode] = heap[currentNode/2];
        currentNode /= 2;
    }
    //终止之后，落座
    heap[currentNode] = x;
}