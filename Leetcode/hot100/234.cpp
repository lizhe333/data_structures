//回文链表
// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        //先判断是奇数还是偶数
        int size=0;
        if(head->next==nullptr){
            return true;
        }
        ListNode* temp=head;
        while(temp!=nullptr){
            temp=temp->next;
            size++;
        }
        //使用快慢指针找位置
        ListNode* slow=head;
        ListNode* fast=head;
        while(fast!=nullptr&&fast->next!=nullptr){
            slow=slow->next;
            fast=fast->next->next;
        }
        //如果是奇数
        if(size%2!=0){
            fast=slow->next;
        }else{
            fast=slow;
        }
        //反转后半部分，需要三个指针
        ListNode* prev=nullptr;
        while(fast!=nullptr){
            ListNode* next=fast->next;
            fast->next=prev;
            prev=fast;
            fast=next;
        }
        //比较
        while (prev != nullptr) {
            if (head->val != prev->val) return false;
            head = head->next;
            prev = prev->next;
        }
        return true;
        
    }
};