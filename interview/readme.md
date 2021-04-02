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
class Solution
{
  public:
    void flatten(TreeNode *root)
    {
        if (!root)
            return;
        flatten(root->left);
        flatten(root->right);
        TreeNode *left = root->left;
        TreeNode *right = root->right;

        // 2、将左子树作为右子树
        root->left = nullptr;
        root->right = left;

        // 3、将原先的右子树接到当前右子树的末端
        TreeNode *p = root;
        while (p->right != nullptr)
        {
            p = p->right;
        }
        p->right = right;
    }
};
```

美团面试题：大意为求滑动窗口的众数

- LFU

```c++
/*
 * 思路：构建优先队列，将根据<数出现的次数，数大小>排序
 */
#include <bits/stdc++.h>
#include <iostream>

using namespace std;

class Node
{
  public:
    int val;
    int freq;
    Node(int v, int f) : val(v), freq(f)
    {
    }
    friend bool operator<(const Node &lhs, const Node &rhs)
    {
        if (lhs.freq == rhs.freq)
            return lhs.val > rhs.val;
        else
            return lhs.freq < rhs.freq;
    }
};

int main(int argc, char const *argv[])
{
    int n, k;
    cin >> n >> k;
    vector<int> nums(n);
    priority_queue<Node> que;
    unordered_map<int, int> m;

    // init
    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
        if (i < k)
        {
            que.push(Node(nums[i], ++m[nums[i]]));
        }
    }
    cout << que.top().val << endl;

    int index = k;
    while (index < n)
    {
        m[nums[index - k]]--;
        m[nums[index]]++;
        que.push(Node(nums[index], m[nums[index]]));
        while (!que.empty())
        {
            Node node = que.top();
            // 如果当前节点的频率和当前哈希表记录的哈希值不一样说明是历史节点，则弹出
            if (node.freq != m[node.val])
            {
                que.pop();
            }
            else
                break;
        }
        cout << que.top().val << endl;
        index++;
    }
    return 0;
}
```

[LeetCode 剑指 Offer 51. 数组中的逆序对](https://leetcode-cn.com/problems/shu-zu-zhong-de-ni-xu-dui-lcof/)

- 思路: 归并

```c++
class Solution {
public:
    int reversePairs(vector<int>& nums) {
        vector<int> tmp(nums.size());
        return mergeSort(0, nums.size() - 1, nums, tmp);
    }
private:
    int mergeSort(int l, int r, vector<int>& nums, vector<int>& tmp) {
        // 终止条件
        if (l >= r) return 0;
        // 递归划分
        int m = (l + r) / 2;
        int res = mergeSort(l, m, nums, tmp) + mergeSort(m + 1, r, nums, tmp);
        // 合并阶段
        int i = l, j = m + 1;
        for (int k = l; k <= r; k++)
            tmp[k] = nums[k];
        for (int k = l; k <= r; k++) {
            if (i == m + 1)
                nums[k] = tmp[j++];
            else if (j == r + 1 || tmp[i] <= tmp[j])
                nums[k] = tmp[i++];
            else {
                nums[k] = tmp[j++];
                res += m - i + 1; // 统计逆序对
            }
        }
        return res;
    }
};

```

LeetCode 440 字典序的第K小数字

```c++

```

LeetCode 42 接雨水

LeetCode 307 区域和检索 - 数组可修改