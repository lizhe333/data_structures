 #include <iostream>
 using namespace std;
 #include <vector>
 //给你一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点
 struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
//法一双重遍历
// class Solution {
// public:
//     ListNode* removeNthFromEnd(ListNode* head, int n) {
//         ListNode* temp=head;
//         int length=0;
//         while(temp!=nullptr){
//             temp=temp->next;
//             length++;
//         }
//         int step=length-n;
//         //如果要删除的是头结点，直接返回第二个节点
//         if(step==0){
//             return head->next;
//         }
//         temp=head;
//         for(int i=0;i<step-1;i++){
//         temp=temp->next;
//         }
//         //删除第step个节点
//         ListNode* temp1=temp->next;
//         temp->next=temp->next->next;
//         delete temp1;
//         return head;
//     }
// };
//法二双指针
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode* fast=head;
    ListNode* slow=head;
    //让快指针先走n步
    for(int i=0;i<n;i++){
        fast=fast->next;
        }
        //如果快指针已经走到末尾，说明要删除的是头结点
        if(fast==nullptr){
            ListNode* temp=head;
            head=head->next;
            delete temp;
            return head;
        }
        //快慢指针同时走，直到快指针走到末尾
        while(fast->next!=nullptr){
            fast=fast->next;
            slow=slow->next;
        }
        //开始进行删除
        ListNode* temp=slow->next;
        slow->next=slow->next->next;
        delete temp;
        return head;
    }
};