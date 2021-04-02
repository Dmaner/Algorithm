# 数组

## 经典例题

### 差分数组

#### [LeetCode 995 K连续位的最小翻转次数](https://leetcode-cn.com/problems/minimum-number-of-k-consecutive-bit-flips/)

- 思路：用差分数组记录每个元素的翻转次数，将O(NK)优化到O(N)

- 代码

```c++
class Solution {
public:
    int minKBitFlips(vector<int> &A, int K) {
        int n = A.size();
        vector<int> diff(n + 1);
        int ans = 0, revCnt = 0;
        for (int i = 0; i < n; ++i) {
            revCnt += diff[i];
            if ((A[i] + revCnt) % 2 == 0) {
                if (i + K > n) {
                    return -1;
                }
                ++ans;
                ++revCnt;
                --diff[i + K];
            }
        }
        return ans;
    }
};
```

### 树状数组

#### [307. 区域和检索 - 数组可修改](https://leetcode-cn.com/problems/range-sum-query-mutable/)

```c++

```

