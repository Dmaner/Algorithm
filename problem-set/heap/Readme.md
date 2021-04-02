# 堆

## 经典例题

#### [LeetCode 1792. 最大平均通过率](https://leetcode-cn.com/problems/maximum-average-pass-ratio/)

- 思路：以增长率作为优先队列的比较值
- 代码

```c++
class Solution {
public:
    double maxAverageRatio(vector<vector<int>>& classes, int extraStudents) {
        priority_queue<tuple<double, int, int>> q;
        
        auto diff = [](int x, int y) -> double {
            return (double)(x + 1) / (y + 1) - (double)x / y;
        };
        
        double ans = 0.;
        for (const auto& c: classes) {
            int x = c[0], y = c[1];
            ans += (double)x / y;
            q.emplace(diff(x, y), x, y);
        }
        while (extraStudents--) {
            auto [d, x, y] = q.top();
            q.pop();
            ans += d;
            q.emplace(diff(x + 1, y + 1), x + 1, y + 1);
        }
        return ans / classes.size();
    }
};
```

