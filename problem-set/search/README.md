# 搜索

## 经典例题

**leetcode 51 N皇后**

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

**leetcode 60 排列序列**
- 问题描述

> 对于数组[1, ... , n]的全排列的第k个

- 思路:


以数组nums = [1, 2, 3, 4, 5, 6]为例
以 1 开头的全排列有 5! 个，以 2 开头的全排列有 5! 个 ...

1. 设 k = 373, 则全排列的第一个数字应该是 nums[ k / 5! ] = 4, 数组删除 4, 此时 nums = [1, 2, 3, 5, 6]; 
2.  k=k\%5!=12  接下来就是在 nums 中找第 12 个全排列，重复以上步骤即可


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

**Leetcode 329 矩阵中的最长递增路径**

- 问题描述

> 给定一个整数矩阵，找出最长递增路径的长度。
> 1.对于每个单元格，你可以往上，下，左，右四个方向移动。 
> 2.你不能在对角线方向上移动或移动到边界外（即不允许环绕）。

- 思路

1.记忆化搜索

- 代码

```c++
class Solution {
 public:
  static constexpr int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
  int rows, columns;

  int longestIncreasingPath(vector<vector<int>> &matrix) {
    if (matrix.size() == 0 || matrix[0].size() == 0) {
      return 0;
    }
    rows = matrix.size();
    columns = matrix[0].size();
    auto memo = vector<vector<int>>(rows, vector<int>(columns));
    int ans = 0;
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < columns; ++j) {
        ans = max(ans, dfs(matrix, i, j, memo));
      }
    }
    return ans;
  }

  int dfs(vector<vector<int>> &matrix, int row, int column,
          vector<vector<int>> &memo) {
    if (memo[row][column] != 0) {
      return memo[row][column];
    }
    ++memo[row][column];
    for (int i = 0; i < 4; ++i) {
      int newRow = row + dirs[i][0];
      int newColumn = column + dirs[i][1];
      if (newRow >= 0 && newRow < rows && newColumn >= 0 &&
          newColumn < columns &&
          matrix[newRow][newColumn] > matrix[row][column]) {
        memo[row][column] =
            max(memo[row][column], dfs(matrix, newRow, newColumn, memo) + 1);
      }
    }
    return memo[row][column];
  }
};
```

**Leetcode 491 递增子序列**

- 问题描述

> 给定一个整型数组, 你的任务是找到所有该数组的递增子序列，递增子序列的长度至少是2。

- 思路

递归枚举子序列模板

```c++
vector<vector<int>> ans;
vector<int> temp;
void dfs(int cur, vector<int>& nums) {
    if (cur == nums.size()) {
        // 判断是否合法，如果合法判断是否重复，将满足条件的加入答案
        if (isValid() && notVisited()) {
            ans.push_back(temp);
        }
        return;
    }
    // 如果选择当前元素
    temp.push_back(nums[cur]);
    dfs(cur + 1, nums);
    temp.pop_back();
    // 如果不选择当前元素
    dfs(cur + 1, nums);
}
```

- 代码

```c++
class Solution {
public:
    vector<int> temp; 
    vector<vector<int>> ans;

    void dfs(int cur, int last, vector<int>& nums) {
        if (cur == nums.size()) {
            if (temp.size() >= 2) {
                ans.push_back(temp);
            }
            return;
        }
        if (nums[cur] >= last) {
            temp.push_back(nums[cur]);
            dfs(cur + 1, nums[cur], nums);
            temp.pop_back();
        }
        if (nums[cur] != last) {
            dfs(cur + 1, last, nums);
        }
    }

    vector<vector<int>> findSubsequences(vector<int>& nums) {
        dfs(0, INT_MIN, nums);
        return ans;
    }
};
```

## 其他例题

- [leetcode 89 格雷码](https://leetcode-cn.com/problems/gray-code/)
- [leetcode 127 单词接龙](https://leetcode-cn.com/problems/word-ladder/)
- [LeetCode 351 安卓系统手势解锁](https://leetcode-cn.com/problems/android-unlock-patterns/)
- [LeetCode 638. 大礼包](https://leetcode-cn.com/problems/shopping-offers/)

## 拓展例题
