# 贪心

## 经典例题

LeetCode 135 分发糖果

```c++
class Solution {
public:
    int candy(vector<int>& ratings) {
        int n = ratings.size();
        vector<int> nums(n, 1);
        for (int i = 1; i < n; i++)
        {
            if (ratings[i-1] < ratings[i])
            {
                nums[i] = nums[i-1] + 1;
            }
        }
        for (int i = n - 2; i >= 0; i--)
        {
            if (ratings[i + 1] < ratings[i])
            {
                nums[i] = max(nums[i], nums[i + 1] + 1);
            }
        }
        return accumulate(nums.begin(), nums.end(), 0);
    }
};
```

LeetCode 605 种花问题

```c++
class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        int size = flowerbed.size();
        for (int i = 0; i < size; i += 2)
        {
            if (flowerbed[i] == 0)
            {
                if (i == size -1 || flowerbed[i+1] == 0)
                {
                    n --;
                }
                else 
                {
                    i ++;
                }
            }
        }
        return n <= 0;
    }
};
```

LeetCode 763 划分字符区间

```c++
class Solution {
public:
    vector<int> partitionLabels(string S) {
        int last[26];
        int length = S.size();
        for (int i = 0; i < length; i++) {
            last[S[i] - 'a'] = i;
        }
        vector<int> partition;
        int start = 0, end = 0;
        for (int i = 0; i < length; i++) {
            end = max(end, last[S[i] - 'a']);
            if (i == end) {
                partition.push_back(end - start + 1);
                start = end + 1;
            }
        }
        return partition;
    }
};
```

LeetCode 406 根据身高重建队列

```c++
class Solution {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        sort(people.begin(), people.end(), [](const vector<int>& u, const vector<int>& v) {
            return u[0] > v[0] || (u[0] == v[0] && u[1] < v[1]);
        });
        vector<vector<int>> ans;
        for (const vector<int>& person: people) {
            ans.insert(ans.begin() + person[1], person);
        }
        return ans;
    }
};
```