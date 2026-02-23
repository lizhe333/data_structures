// 给你链表的头节点 head ，每 k 个节点一组进行翻转，请你返回修改后的链表。

// k 是一个正整数，它的值小于或等于链表的长度。如果节点总数不是 k 的整数倍，那么请将最后剩余的节点保持原有顺序。

// 你不能只是单纯的改变节点内部的值，而是需要实际进行节点交换。
 #include <iostream>
 using namespace std;
 #include <vector>
 #include <algorithm>
 struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
class Solution {
public:
//反转一个子链表，并返回头节点和尾节点
     pair<ListNode*, ListNode*>* myreverse(ListNode*head,ListNode* tail){
        ListNode*pre=tail->next;
        ListNode*cur=head;
        while(pre!=tail){
            ListNode* temp=cur->next;
            cur->next=pre;
            pre=cur;
            cur=temp;
        }
        return new pair<ListNode*, ListNode*>(tail, head);
     }
    ListNode* reverseKGroup(ListNode* head, int k) {
        
    }
};