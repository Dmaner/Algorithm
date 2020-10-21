// leetcode 743  link: https://leetcode-cn.com/problems/network-delay-time/
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    int networkDelayTime(vector<vector<int>> &times, int n, int K)
    {
        const int inf = 0x3f3f3f3f;
        int cost[n + 1][n + 1];
        bool visited[n + 1];
        int dist[n + 1];
        memset(cost, inf, sizeof(cost));
        memset(visited, false, sizeof(visited));
        memset(dist, inf, sizeof(dist));

        int ans = 0;

        for (auto t : times)
        {
            cost[t[0]][t[1]] = t[2];
        }

        dist[K] = 0;
        for (int i = 1; i <= n; i++)
        {
            int index = -1;
            int values = inf;

            // find the nearest node
            for (int i = 1; i <= n; i++)
            {
                if (!visited[i] && dist[i] < values)
                {
                    index = i;
                    values = dist[i];
                }
            }
            if (index == -1)
                return -1;
            visited[index] = true;
            ans = max(ans, values);

            // update cost
            for (int i = 1; i <= n; i++)
            {
                if (!visited[i])
                    dist[i] = min(dist[i], dist[index] + cost[index][i]);
            }
        }
        return ans;
    }


};
