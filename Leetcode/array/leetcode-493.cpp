// leetcode 493 link: https://leetcode-cn.com/problems/reverse-pairs/
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
    void updateTree(int i)
    {
        while (i < size)
        {
            tree[i] ++;
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
    
    int get_bucket_id(vector<int> &v, int num) 
    {
        return lower_bound(v.begin(), v.end(), num) - v.begin();
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

        // 离散化
        vector<int> v(nums);
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());

        int count = 0;
        // 从后向前遍历
        for (int i = size - 1; i >= 0; --i)
        {
            // 查找num/2
            count += ft.queryTree(ft.get_bucket_id(v, ceil(nums[i]/2.)));
            // 更新num
            ft.updateTree(ft.get_bucket_id(v, nums[i]) + 1);
        }
        return count;
    }
};