# 栈

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