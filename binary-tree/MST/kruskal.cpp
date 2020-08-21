// leetcode 1135 links :https://leetcode-cn.com/problems/connecting-cities-with-minimum-cost/
#include <bits/stdc++.h>

using namespace std;

class Solution {
private:
    vector<int> pre;
    vector<int> size;
public:
    int find(int x)
    {
        int root = x;
        int record = x;
        while (root != pre[root]) root = pre[root];

        // compress path
        while (record != root)
        {
            int temp = pre[record];
            pre[record] = root;
            record = temp;
        }
        return root;
    }
    void unite(int x, int y)
    {
        if (size[x] < size[y]) swap(x, y);
        pre[y] = x;
        size[x] += size[y];
    }
    int minimumCost(int N, vector<vector<int>>& connections) {
        // initialize
        pre = vector<int>(N+1);
        iota(pre.begin(), pre.end(), 0);
        size = vector<int>(N+1, 1);
        sort(connections.begin(), connections.end(), [](vector<int> &a, vector<int>&b)->bool{return a[2] < b[2];});
        int ans = 0;
        int edges = 0;
        for (int i = 0; i < connections.size(); i++)
        {
            vector<int> temp = connections[i];
            int a = temp[0];
            int b = temp[1];
            int cost = temp[2];
            int root_a = find(a);
            int root_b = find(b);
            if (root_a != root_b)
            {
                unite(root_a, root_b);
                ans += cost;
                edges ++;
            }
            if (edges == N-1) return ans;
        }
        return -1;
    }
};