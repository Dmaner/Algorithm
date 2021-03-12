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
- mmap
- mmu
- 共享内存
- 系统调用
- 进程内存布局
- 进程初始化

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

LeetCode 114 二叉树展开为链表

```c++
class Solution {
public:
    void flatten(TreeNode* root) {
        TreeNode *curr = root;
        while (curr != nullptr) {
            if (curr->left != nullptr) {
                auto next = curr->left;
                auto predecessor = next;
                while (predecessor->right != nullptr) {
                    predecessor = predecessor->right;
                }
                predecessor->right = curr->right;
                curr->left = nullptr;
                curr->right = next;
            }
            curr = curr->right;
        }
    }
};
```

```c++
class Solution {
public:
    void flatten(TreeNode* root) {
        if(!root)return;
        flatten(root->left);
        flatten(root->right);
    TreeNode* left = root->left;
    TreeNode *right = root->right;

    // 2、将左子树作为右子树
    root->left = nullptr;
    root->right = left;

    // 3、将原先的右子树接到当前右子树的末端
    TreeNode* p = root;
    while (p->right != nullptr) {
        p = p->right;
    }
    p->right = right;
    }
};
```

LeetCode 440 字典序的第K小数字

```c++

```

LeetCode 42 接雨水

LeetCode 307 区域和检索 - 数组可修改