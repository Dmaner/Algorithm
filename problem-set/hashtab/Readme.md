# 哈希表

## 经典例题

LeetCode 128 最长连续序列

```c++
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> s;
        for (const int& num : nums)
        {
            s.insert(num);
        }
        int ans = 0;
        for (const int& num: nums)
        {
            int temp = num;
            int res = 1;
            if (!s.count(num-1))
            {
                temp ++;
                while (s.count(temp))
                {
                    temp ++;
                    res ++;
                }
                ans = max(ans, res);
            }
        }
        return ans;
    }
};
```

LeetCode 