#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>
// 给你链表的头结点 head ，请将其按 升序 排列并返回 排序后的链表 
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        ListNode* temp = head;
        vector<int> vec;
        while(temp!=nullptr){
            vec.push_back(temp->val);
            temp=temp->next;
        }
        sort(vec.begin(),vec.end());
        int n=vec.size();
        //构建新的链表
        ListNode* newhead = new ListNode(vec[0]);
        ListNode* node = newhead;
        for(int i=1;i<n;i++){
            ListNode* node = new ListNode(vec[i]);
            newhead->next = node;
            newhead = newhead->next;
        }
        return node;
    }
};