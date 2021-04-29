# 面试高频题

[接雨水](https://leetcode-cn.com/problems/trapping-rain-water/)

- 代码

```c++
class Solution {
public:
    int trap(vector<int>& height) {
        int ans = 0;
        int left = 0, right = height.size() - 1;
        int leftMax = 0, rightMax = 0;
        while (left < right) {
            leftMax = max(leftMax, height[left]);
            rightMax = max(rightMax, height[right]);
            if (height[left] < height[right]) {
                ans += leftMax - height[left++];
            } else {
                ans += rightMax - height[right--];
            }
        }
        return ans;
    }
};
```

[正则表达式](https://leetcode-cn.com/problems/regular-expression-matching/)

- 代码

```c++
class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.length();
        int n = p.length();
        bool dp[m+1][n+1];
        dp[0][0] = true;

        // base case
        for (int i = 1; i <= m; i++) dp[i][0] = false;
        for (int i = 1; i <= n; i++)
        {
            if (i >= 2 && p[i-1] == '*') dp[0][i] = dp[0][i-2];
            else dp[0][i] = false;
        }

        for (int i = 1; i <= m; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (p[j-1] == '.' || p[j-1] == s[i-1]) dp[i][j] = dp[i-1][j-1];
                else if (p[j-1] == '*') 
                {
                    dp[i][j] = dp[i][j-2];
                    if (s[i-1] == p[j-2] || p[j-2] == '.') dp[i][j] |= dp[i-1][j];
                }
                else dp[i][j] = false;
            }
        }
        return dp[m][n];
    }
};
```

