# 搜索

## 经典例题

leetcode 51 N皇后

- 问题描述
> n 皇后问题研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击，给定一个整数 n，返回所有不同的 n 皇后问题的解决方案

- 代码
```c++
// 解法一: 回溯法

class Solution {
 private:
  vector<bool> col_vis;   /* 保存占有列 */
  vector<bool> l_dia_vis; /* 保存两个对角占有情况 */
  vector<bool> r_dia_vis;

 public:
  void back(vector<vector<string>> &ans, vector<string> &board, int n,
            int queens) {
    if (n == queens) {
      ans.push_back(board);
    } else {
      int total = 0;
      for (int i = 0; i < n; i++) {
        if (col_vis[i] && l_dia_vis[queens + i] &&
            r_dia_vis[queens - i + n - 1]) {
          col_vis[i] = false;
          l_dia_vis[queens + i] = false;
          r_dia_vis[queens - i + n - 1] = false;
          board[queens][i] = 'Q';
          back(ans, board, n, queens + 1);
          board[queens][i] = '.';
          col_vis[i] = true;
          l_dia_vis[queens + i] = true;
          r_dia_vis[queens - i + n - 1] = true;
        }
      }
    }
  }
  vector<vector<string>> solveNQueens(int n) {
    vector<string> tmp;
    vector<vector<string>> ans;
    /* 初始化 */
    col_vis = vector<bool>(n, true);
    l_dia_vis = vector<bool>(n * 2, true);
    r_dia_vis = vector<bool>(n * 2, true);
    for (int i = 0; i < n; i++) {
      tmp.push_back(string(n, '.'));
    }
    
    back(ans, tmp, n, 0);
    return ans;
  }
};

```

leetcode 60 排列序列
- 问题描述

> 对于数组[1, ... , n]的全排列的第k个

- 思路:


以数组$nums = [1, 2, 3, 4, 5, 6]$为例
以 1 开头的全排列有 $5!$ 个，以 2 开头的全排列有 $5!$ 个 ...

1. 设 $k = 373$, 则全排列的第一个数字应该是 $nums[ k / 5! ] = 4$, 数组删除 $4$, 此时 $nums = [1, 2, 3, 5, 6]$; 
2. $ k=k\%5!=12 $ 接下来就是在 $nums$ 中找第 12 个全排列，重复以上步骤即可


```c++
class Solution {
public:
    string getPermutation(int n, int k) {
        vector<int> factorial(n);
        factorial[0] = 1;
        for (int i = 1; i < n; i++) {
            factorial[i] = i * factorial[i - 1];
        }
        k--;
        string ans;
        vector<int> nums;
        for (int i = 1; i <= n; i++) {
            nums.push_back(i);
        }
        for (int i = 1; i <= n; i++) {
            int order = k / factorial[n - i];
            ans += (nums[order] + '0');
            for (int j = order; j < n - i; j++) {
                nums[j] = nums[j + 1];
            }
            k %= factorial[n - i];
        }
        return ans;
    }
};
```

## 拓展例题

## 其他例题

- leetcode 89 格雷码
- leetcode 127 单词接龙