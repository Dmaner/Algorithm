// leetcode 315 line: https://leetcode-cn.com/problems/count-of-smaller-numbers-after-self/
#include <bits/stdc++.h>

using namespace std;

class Solution
{
private:
    vector<int> bits;
    vector<int> preprocess;

    // 离散化
    void discretization(vector<int> &nums)
    {
        preprocess.assign(nums.begin(), nums.end());
        sort(preprocess.begin(), preprocess.end());
        preprocess.erase(unique(preprocess.begin(), preprocess.end()), preprocess.end());
    }

    inline int lowbit(int x) { return x & (-x); }

    inline int get_id(int x)
    {
        return lower_bound(preprocess.begin(), preprocess.end(), x) - preprocess.begin() + 1;
    }

public:
    int query(int pos)
    {
        int res = 0;
        while (pos > 0)
        {
            res += bits[pos];
            pos -= lowbit(pos);
        }
        return res;
    }

    void update(int id)
    {
        while (id < bits.size())
        {
            bits[id]++;
            id += lowbit(id);
        }
    }

    vector<int> countSmaller(vector<int> &nums)
    {
        vector<int> results;

        int n = nums.size();
        bits.resize(n + 1);
        discretization(nums);

        for (int i = n - 1; i >= 0; --i)
        {
            int bukets_id = get_id(nums[i]);
            results.push_back(query(bukets_id - 1));
            update(bukets_id);
        }
        reverse(results.begin(), results.end());
        return results;
    }
};