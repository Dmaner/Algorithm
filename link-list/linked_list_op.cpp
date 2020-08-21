#include "Node.hpp"
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

// build sample list
ListNode* get_sample(vector<int>& nums)
{
    ListNode* head = new ListNode(0);
    ListNode* temp = head;
    for (int& num: nums)
    {
        temp->next = new ListNode(num);
        temp = temp->next;
    }
    return head->next;
}

ListNode* get_sample(vector<int> &&nums)
{
    ListNode* head = new ListNode(0);
    ListNode* temp = head;
    for (int& num: nums)
    {
        temp->next = new ListNode(num);
        temp = temp->next;
    }
    return head->next;
}

// print node 
void print_node(ListNode* node)
{
    ListNode* head = node;
    while (head)
    {
        if (head->next) cout << "Node: "<<head->val << " -> ";
        else cout << "Node: "<<head->val << endl;   
        head = head->next;
    }
}

// reverse node list
ListNode* reverselist(ListNode* node, ListNode* pre = nullptr)
{
    if (!node) return pre;
    ListNode* next = node->next;
    node->next = pre;
    return reverselist(next, node);
}

ListNode* reverselist2(ListNode* node)
{
    ListNode* pre = nullptr;
    while (node)
    {
        ListNode* next = node->next;
        node->next = pre;
        pre = node;
        node = next;
    }
    return pre;
}

// add two increasing linked list
ListNode* MergeTwoList(ListNode* l1, ListNode* l2)
{
    ListNode* dummy = new ListNode(0);
    ListNode* temp = dummy;
    while (l1 && l2)
    {
        if (l1->val > l2->val) 
        {
            temp->next = l2;
            l2 = l2->next;
        }
        else 
        {
            temp->next = l1;
            l1 = l1->next;
        }
        temp = temp->next;
    }
    temp->next = l1 ? l1 : l2;
    return dummy->next;
}

// find middle node
void FindMidNode(ListNode* head)
{
    if (!head) cout << "List is empty\n";
    else
    {
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast->next && fast->next->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        cout << "Midden Node : " << slow->val << endl;
    }
}

int main(int argc, char const *argv[])
{
    vector<int> temp;
    ListNode* sample;
    // test reverslist
    cout << "test reverslist" << endl;
    temp = vector<int> {1, 2, 3, 4};
    sample = get_sample(temp);
    sample = reverselist(sample);
    print_node(sample);
    sample = reverselist2(sample);
    print_node(sample);

    // test merget two list
    cout << "test merge two list" << endl;
    ListNode* merge1 = get_sample(vector<int> {1, 2, 5});
    ListNode* merge2 = get_sample(vector<int> {3, 4});
    ListNode* merge_result = MergeTwoList(merge1, merge2);
    print_node(merge_result);
    
    // test find middle node
    cout << "test find middle node" << endl;
    ListNode* middle1 = get_sample(vector<int> {1, 2, 3});
    ListNode* middle2 = get_sample(vector<int> {1, 2, 3, 4, 5, 6});
    FindMidNode(middle1);
    FindMidNode(middle2);

    return 0;
}
