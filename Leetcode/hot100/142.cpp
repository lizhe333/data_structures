/*给定一个链表的头节点  head ，返回链表开始入环的第一个节点。 如果链表无环，则返回 null。

如果链表中有某个节点，可以通过连续跟踪 next 指针再次到达，则链表中存在环。 为了表示给定链表中的环，评测系统内部使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。如果 pos 是 -1，则在该链表中没有环。注意：pos 不作为参数进行传递，仅仅是为了标识链表的实际情况。

不允许修改 链表。
*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
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
    ListNode *detectCycle(ListNode *head) {
        ListNode* prev = nullptr;
        ListNode* slow = head;
        ListNode* fast=head;
        int flage=0;
        while(fast!=nullptr&&fast->next!=nullptr){
            slow=slow->next;
            fast=fast->next->next;
            if(slow==fast){
            flage=1;
            break;
            }
        }
        if(flage==0){
            return nullptr;
        }
        //如果有环则需要找到环的起点
        //由数学推导可知，当快慢指针相遇时，慢指针走了k步，快指针走了2k步
        //假设环的长度为n，那么快指针比慢指针多走了n步
        //即2k-k=n
        //即k=n
        //所以当快慢指针相遇时，慢指针再走n步就到了环的起点
        //而头节点到环的起点的距离也为n
        //所以当快慢指针相遇时，头节点和慢指针同时走，相遇点就是环的起点
        slow=head;
        while(slow!=fast){
            slow=slow->next;
            fast=fast->next;
        }
        return slow;
    };
};