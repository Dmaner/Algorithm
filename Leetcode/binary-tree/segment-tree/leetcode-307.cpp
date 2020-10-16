// leetcode 307 link: https://leetcode-cn.com/problems/range-sum-query-mutable/
#include <bits/stdc++.h>

using namespace std;

class NumArray {
public:
    vector<int> tree;
    int n;
    NumArray(vector<int>& nums) {
        n = nums.size();
        tree = vector<int> (n * 2);
        for (int i = n; i < 2* n; i++) tree[i] = nums[i-n];
        for (int i = n-1; i > 0; i--) tree[i] = tree[i*2] + tree[i*2 + 1];
    }
    
    void update(int i, int val) {
        int pos = n + i;
        tree[pos] = val;
        while (pos > 0)
        {
            int left = pos % 2 == 0 ? pos : pos -1;
            int right = pos % 2 == 0 ? pos + 1: pos;
            tree[pos/2] = tree[left] + tree[right];
            pos /= 2;
        }
    }
    
    int sumRange(int i, int j) {
        int sum = 0;
        int l = n + i;
        int r = n + j;
        while ( l <= r)
        {
            // 如果左区间是左节点则直接根据父节点计算
            // 否则增加节点值
            if (l % 2 == 1) 
            {
                sum += tree[l];
                l ++;
            }
            if (r % 2 == 0) 
            {
                sum += tree[r];
                r --;
            }
            r /= 2;
            l /= 2;
        }
        return sum;
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(i,val);
 * int param_2 = obj->sumRange(i,j);
 */