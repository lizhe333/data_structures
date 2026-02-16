/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
 struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int carry=0;
        ListNode* head=new ListNode();
        ListNode* temp=head;
        while(l1!=nullptr||l2!=nullptr){
            //计算相加
            ListNode*result=new ListNode();
            int sum=carry;
            if(l1!=nullptr){
                sum+=l1->val;
                l1=l1->next;
            }
            if(l2!=nullptr){
                sum+=l2->val;
                l2=l2->next;
            }
            result->val=sum%10;
            carry=sum/10;
            //将结果连接回结果链表
         
                temp->next=result;
                temp=temp->next;
            
        }
        //如果最后还有进位，需要添加一个节点
        if(carry!=0){
            temp->next=new ListNode(carry);
        }
        return head->next;
    }
};