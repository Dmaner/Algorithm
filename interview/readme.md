# 记录面试遇到的算法题

## 重点

- 回文
- 二分
- topk
- DP
- 二叉树
- 最短路径
- 最小生成树
- 拓扑排序
- 并查集

## 

LeetCode 142 环形链表

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode* fast = head;
        ListNode* slow = head;
        while(fast != NULL && fast->next != NULL) {
            slow = slow->next;
            fast = fast->next->next;
            // 快慢指针相遇，此时从head 和 相遇点，同时查找直至相遇
            if (slow == fast) {
                ListNode* index1 = fast;
                ListNode* index2 = head;
                while (index1 != index2) {
                    index1 = index1->next;
                    index2 = index2->next;
                }
                return index2; // 返回环的入口
            }
        }
        return NULL;
    }
};
```

LeetCode 440 字典序的第K小数字

```c++

```

LeetCode 42 接雨水

LeetCode 307 区域和检索 - 数组可修改