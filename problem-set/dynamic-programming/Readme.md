# 动态规划

## 经典例题

[LeetCode 354.俄罗斯套娃信封问题](https://leetcode-cn.com/problems/russian-doll-envelopes/)

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

[LeetCode 918 环形子数组的最大和](https://leetcode-cn.com/problems/maximum-sum-circular-subarray/)

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

[LeetCode 873 最长的斐波那契子序列的长度](https://leetcode-cn.com/problems/length-of-longest-fibonacci-subsequence/)

- 思路

难点在于对状态的定义, 对于一个斐波那契子序列, 需要知道两个状态才能判断是不是可以转移
定义**状态**为`dp[i][j]`表示以`arr[i], arr[j]`结尾最长的斐波那契子序列
**状态转移方程** :  `dp[i][j] = max(dp[k][i] + 1)`其中`k < i < j`且`arr[i] + arr[k] = arr[j]`

- 代码

```c++
class Solution {
public:
    int lenLongestFibSubseq(vector<int>& arr) {
        int n = arr.size();
        unordered_map<int, int> index_map;
        for (int i = 0; i < n; i++)
        {
            index_map[arr[i]] = i;
        }
        unordered_map<int, int> dp;
        int ans = 0;
        for (int j = 0; j < n; j++)
        {
            for (int i = 0; i < j; i++)
            {
                if (arr[j] - arr[i] < arr[i] && index_map.count(arr[j] - arr[i]))
                {
                    int k = index_map[arr[j] - arr[i]];
                    dp[j*n + i] = dp[i*n + k] + 1;
                    ans = max(dp[j*n+i] + 2, ans);
                }
            }
        }
        return ans;
    }
};
```

[LeetCode 91. 解码方法](https://leetcode-cn.com/problems/decode-ways/)

- 思路: 分类讨论搞搞清

- 代码

```c++
class Solution {
public:
    int numDecodings(string s) {
        if (s[0] == '0') return 0;
        int pre = 1, curr = 1;//dp[-1] = dp[0] = 1
        for (int i = 1; i < s.size(); i++) {
            int tmp = curr;
            if (s[i] == '0')
                if (s[i - 1] == '1' || s[i - 1] == '2') curr = pre;
                else return 0;
            else if (s[i - 1] == '1' || (s[i - 1] == '2' && s[i] >= '1' && s[i] <= '6'))
                curr = curr + pre;
            pre = tmp;
        }
        return curr;
    }
};
```

[LeetCode 813. 最大平均值和的分组](https://leetcode-cn.com/problems/largest-sum-of-averages/)

- 代码
  
```c++
class Solution {
public:
    double largestSumOfAverages(vector<int>& nums, int K) {
        int n = nums.size();
        vector<double> sum(n+1, 0);
        vector<vector<double>> dp(n + 1, vector<double>(K+1, 0));

        // presum
        for (int i = 1; i <= n; i++) sum[i] = sum[i-1] + nums[i-1];
        
        // base case
        for (int i = 1; i <= n; i++)
        {
            dp[i][1] = sum[i] / i;
        }
        
        for (int i = 1; i <= n; i++)
        {
            for (int j = 2; j <= K; j++)
            {
                for (int k = j - 1; k < i; k++)
                {
                    dp[i][j] = max(dp[i][j], dp[k][j-1] + (sum[i] - sum[k]) / (i - k));
                }
            }
        }
        
        return dp[n][K];
    }
};
```

[LeetCode 10 正则表达式匹配](https://leetcode-cn.com/problems/regular-expression-matching/)

- 思路：写出dp方程

```c++
if s[i] == p[i] || p[i] == '.' :
    dp[i][j] = dp[i-1][j-1]
else if p[i] == '*':
    if s[i] == p[i-1] || p[i-1] == '.' :
        dp[i][j] = dp[i][j-2] || dp[i-1][j]
    else 
        dp[i][j] = dp[i][j-2]
```

- 代码：

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

[LeetCode 174 地下城游戏](https://leetcode-cn.com/problems/dungeon-game/)

- 思路：正向dp的话需要记录当前路径和以及当前路径最小值对然而对一个参数的优化会对另一个参数的优化产生影响，但反向dp就能很好解决这个问题

- 代码：

```c++
class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int n = dungeon.size(), m = dungeon[0].size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, INT_MAX));
        dp[n][m - 1] = dp[n - 1][m] = 1;
        for (int i = n - 1; i >= 0; --i) {
            for (int j = m - 1; j >= 0; --j) {
                int minn = min(dp[i + 1][j], dp[i][j + 1]);
                dp[i][j] = max(minn - dungeon[i][j], 1);
            }
        }
        return dp[0][0];
    }
};
```

[LeetCode 1371 每个元音包含偶数次的最长子字符串](https://leetcode-cn.com/problems/find-the-longest-substring-containing-vowels-in-even-counts/)

- 思路：前缀和+状态压缩
- 代码：

```c++
class Solution {
public:
    int findTheLongestSubstring(string s) {
        int ans = 0, status = 0, n = s.length();
        vector<int> pos(1 << 5, -1);
        pos[0] = 0;
        for (int i = 0; i < n; ++i) {
            if (s[i] == 'a') {
                status ^= 1<<0;
            } else if (s[i] == 'e') {
                status ^= 1<<1;
            } else if (s[i] == 'i') {
                status ^= 1<<2;
            } else if (s[i] == 'o') {
                status ^= 1<<3;
            } else if (s[i] == 'u') {
                status ^= 1<<4;
            }
            if (~pos[status]) {
                ans = max(ans, i + 1 - pos[status]);
            } else {
                pos[status] = i + 1;
            }
        }
        return ans;
    }
};
```

[LeetCode 523 连续的子数组和](https://leetcode-cn.com/problems/continuous-subarray-sum/)

- 代码：

```c++
class Solution {
public:
// 转换为求sum=0的情况
    bool checkSubarraySum(vector<int>& nums, int k) {
        map<int, int> mp;
        mp[0] = -1;
        int sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
            if (k != 0) sum %= k;
            if (mp.find(sum) != mp.end()) {
                if (i - mp[sum] > 1) return true; 
            } else {
                mp[sum] = i;
            }
        }
        return false;
    }
};
```

[LeetCode 1447 找两个和为目标值且不重叠的子数组](https://leetcode-cn.com/problems/find-two-non-overlapping-sub-arrays-each-with-target-sum/)
- 思路: 滑动窗口+dp保存状态

- 代码
```c++
class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();
        int left = 0;
        int right = 0;
        int sum = 0;
        int ans = INT_MAX;
        // dp[i]表示区间[0,i-1]之间最短的和为target的子数组
        // n + 1表示不存在
        vector<int> dp(n + 1, 0);
        dp[0] = n + 1; 

        for (right = 0; right < n; right++) {
            sum += arr[right];

            while (sum > target) {
                sum -= arr[left];
                left++;
            }

            if (sum == target) {
                // 区间[left,right]是一个和为target的子数组，该子数组长度为len
                int len = right - left + 1;
                ans = min(ans, len + dp[left]);
                // 更新dp，取长度更小的一个
                dp[right + 1] = min(dp[right], len);
            } else {
                dp[right + 1] = dp[right];
            }
        }

        return ans > n ? -1 : ans;
    }
};
```

[LeetCode 370 区间加法](https://leetcode-cn.com/problems/range-addition/)

- 思路：差分
- 代码

```c++
class Solution {
public:
    vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
        vector<int> ans(length);
        for (auto& op : updates)
        {
            int start = op[0];
            int end = op[1];
            int inc = op[2];
            ans[start] += inc;
            if (end + 1 < length) ans[end+1] -= inc;
        }

        for (int i = 1; i < length; i++)
        {
            ans[i] += ans[i-1];
        }
        return ans;
    }
};
```


## 其他例题

- LeetCode 打家劫舍
- LeetCode 股票系列
- [LeetCode 面试题 17.24 最大子矩阵](https://leetcode-cn.com/problems/max-submatrix-lcci/)
- [LeetCode 887 鸡蛋掉落](https://leetcode-cn.com/problems/super-egg-drop/)
- [LeetCode 975 奇偶跳](https://leetcode-cn.com/problems/odd-even-jump/)
- [LeetCode 403 青蛙过河](https://leetcode-cn.com/problems/frog-jump/)
- [LeetCode 1478 安排邮筒](https://leetcode-cn.com/problems/allocate-mailboxes/)
- [LeetCode 87 扰乱字符串](https://leetcode-cn.com/problems/scramble-string/)
- [LeetCode 650 只有两个键的键盘](https://leetcode-cn.com/problems/2-keys-keyboard/)
- [LeetCode 974 和可被 K 整除的子数组](https://leetcode-cn.com/problems/subarray-sums-divisible-by-k/)
- [LeetCode 1074 元素和为目标值的子矩阵数量](https://leetcode-cn.com/problems/number-of-submatrices-that-sum-to-target/)
- [LeetCode 5 最长回文串](https://leetcode-cn.com/problems/longest-palindromic-substring/)


## 拓展例题

- [LeetCode 1388 3n披萨](https://leetcode-cn.com/problems/pizza-with-3n-slices/)