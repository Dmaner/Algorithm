#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

struct FinTree
{
    vector<int> tree;
    int size;
    FinTree(int _size) : size(_size)
    {
        tree = vector<int>(size, 0);
    };

    int lowbit(int n)
    {
        return n & (-n);
    }

    // 向上更新
    void updateTree(int i, int count)
    {
        while (i < size)
        {
            tree[i] += count;
            i += lowbit(i);
        }
    }

    // 向下统计
    int queryTree(int i)
    {
        int res = 0;
        while (i > 0)
        {
            res += tree[i];
            i -= lowbit(i);
        }
        return res;
    }
};

class Solution
{
public:
    int reversePairs(vector<int> &nums)
    {
        int size = nums.size();
        if (size == 0)
            return 0;
        FinTree ft(size + 1);

        // 离散化 排序去重 用Set也行
        vector<int> v(nums);
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());

        int count = 0;
        // 从后向前遍历
        for (int i = size - 1; i >= 0; --i)
        {
            // 查找num/2
            count += ft.queryTree(lower_bound(v.begin(), v.end(), ceil(nums[i] / 2.)) - v.begin());
            // 更新num
            ft.updateTree(lower_bound(v.begin(), v.end(), nums[i]) - v.begin() + 1, 1);
        }
        return count;
    }
};