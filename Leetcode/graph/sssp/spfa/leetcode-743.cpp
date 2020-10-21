// leetcode 743  link: https://leetcode-cn.com/problems/network-delay-time/
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    int networkDelayTime(vector<vector<int>> &times, int N, int K)
    {
        const int INF = 0x3f3f3f3f;
        vector<int> dist(N + 1, INF);  // 保存到起点的距离
        vector<bool> st(N + 1, false); // 是否最短
        typedef pair<int, int> PII;
        unordered_map<int, vector<PII>> edges; // 邻接表

        queue<int> q;
        q.push(K);
        dist[K] = 0;
        st[K] = true; // 是否在队列中

        for (auto &t : times)
        {
            edges[t[0]].push_back({t[1], t[2]});
        }

        while (!q.empty())
        { // 当没有点可以更新的时候，说明得到最短路
            auto t = q.front();
            q.pop();
            st[t] = false;
            for (auto &e : edges[t])
            { // 更新队列中的点出发的 所有边
                int v = e.first, w = e.second;
                if (dist[v] > dist[t] + w)
                {
                    dist[v] = dist[t] + w;
                    if (!st[v])
                    {
                        q.push(v);
                        st[v] = true;
                    }
                }
            }
        }
        int ans = *max_element(dist.begin() + 1, dist.end());
        return ans == INF ? -1 : ans;
    }
};