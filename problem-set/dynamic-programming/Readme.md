# 动态规划

## 经典例题

[**LeetCode 354.俄罗斯套娃信封问题**](https://leetcode-cn.com/problems/russian-doll-envelopes/)

- 思路

将信封按`w`升序排序, 相同的`w`按`h`降序排, 然后就是对`h`维度进行最大上升子序的列的查找

- 代码

```c++
class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        if (envelopes.size() == 0) return 0;
        auto f = [](vector<int>& a, vector<int>&b) {
            if (a[0] == b[0]) return a[1] > b[1];
            else return a[0] < b[0];
        };
        sort(envelopes.begin(), envelopes.end(), f);
        int n = envelopes.size();
        vector<int> dp(n+1, 0);
        dp[1] = envelopes[0][1];
        int len = 1;
        for (int i = 1; i < envelopes.size(); i++)
        {
            int h = envelopes[i][1];
            if (h > dp[len]) dp[++len] = h;
            else 
            {
                int l = 0;
                int r = len;
                while (l < r) 
                {
                    int mid = l + (r - l) / 2;
                    if (dp[mid] < h) l = mid + 1;
                    else r = mid;
                }
                dp[l] = h;
            }
        }
        return len;
    }
};
```

[**LeetCode 918 环形子数组的最大和**](https://leetcode-cn.com/problems/maximum-sum-circular-subarray/)

- 题意

求环形数组的最大子段和

- 思路

最大子段和区间, 对于`0 <= i <= j <= N`，在`[i, j]`或者`[0, i]`和`[j, N]`之一

- 代码

```c++
class Solution {
public:
    int kadane(vector<int>& A, int left, int right, int sign)
    {
        int cur = INT_MIN;
        int ans = INT_MIN;
        for (int i = left; i < right; i++)
        {
            int num = sign * A[i];
            cur = num + max(cur, 0);
            ans = max(ans, cur);
        }
        return ans;
    }
    int maxSubarraySumCircular(vector<int>& A) {
        int n = A.size();
        if (n == 1) return A[0];
        int sum = 0;
        for (auto num: A) sum += num;
        int ans_1 = kadane(A, 0, n, 1);
        int ans_2 = sum + kadane(A, 0, n-1, -1);
        int ans_3 = sum + kadane(A, 1, n, -1);
        return max(ans_1, max(ans_2, ans_3));
    }
};
```

## 其他例题

- [面试题 17.24 最大子矩阵](https://leetcode-cn.com/problems/max-submatrix-lcci/)
- LeetCode 打家劫舍

## 拓展例题

- [LeetCode 1388 3n披萨](https://leetcode-cn.com/problems/pizza-with-3n-slices/)