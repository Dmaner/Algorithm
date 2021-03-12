# 栈

## 经典算法

[单调栈](https://zhuanlan.zhihu.com/p/61423849)


## 经典例题

LeetCode 239 滑动窗口最大值

```c++
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        deque<int> q;
        for (int i = 0; i < k; i++)
        {
            int num = nums[i];
            while (!q.empty() && q.back() < num) 
            {
                q.pop_back();
            }
            q.push_back(num);
        }
        vector<int> ans = {q.front()};
        for (int i = k; i < n; i++)
        {
            int num = nums[i];
            while (!q.empty() && q.back() < num)
            {
                q.pop_back();
            }
            q.push_back(num);
            if (q.front() == nums[i-k]) q.pop_front();
            ans.push_back(q.front());
        }
        return ans;
    }
};
```

LeetCode 331 验证二叉树的前序序列化

栈

```c++
class Solution {
public:
    bool isValidSerialization(string preorder) {
        int n = preorder.length();
        int i = 0;
        stack<int> stk;
        stk.push(1);
        while (i < n) {
            if (stk.empty()) {
                return false;
            }
            if (preorder[i] == ',') {
                i++;
            } else if (preorder[i] == '#'){
                stk.top() -= 1;
                if (stk.top() == 0) {
                    stk.pop();
                }
                i++;
            } else {
                // 读一个数字
                while (i < n && preorder[i] != ',') {
                    i++;
                }
                stk.top() -= 1;
                if (stk.top() == 0) {
                    stk.pop();
                }
                stk.push(2);
            }
        }
        return stk.empty();
    }
};
```

计数法

```c++
class Solution {
public:
    bool isValidSerialization(string preorder) {
        int n = preorder.length();
        int i = 0;
        int slots = 1;
        while (i < n) {
            if (slots == 0) {
                return false;
            }
            if (preorder[i] == ',') {
                i++;
            } else if (preorder[i] == '#'){
                slots--;
                i++;
            } else {
                // 读一个数字
                while (i < n && preorder[i] != ',') {
                    i++;
                }
                slots++; // slots = slots - 1 + 2
            }
        }
        return slots == 0;
    }
};
```