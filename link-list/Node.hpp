#ifndef NODE_H
#define NODE_H

class ListNode {
 public:
  int val;
  ListNode* next;
  ListNode(int value) : val(value), next(nullptr) {}
};

#endif