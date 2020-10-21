// leetcode 743  link: https://leetcode-cn.com/problems/network-delay-time/
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Node
{
public:
    int id;
    int cost;
    Node(int v, int c) : id(v), cost(c) {}
    bool operator<(const Node &rhs) const
    {
        return cost > rhs.cost;
    }
};

class Edge
{
public:
    int point;
    int cost;
    Edge(int p, int c) : point(p), cost(c) {}
};

class Solution
{
public:
    int networkDelayTime(vector<vector<int>> &times, int n, int K)
    {
        const int INF = 0x3f3f3f3f;
        vector<vector<Edge>> graph(n + 1, vector<Edge>());
        vector<int> dist(n+1, INF);
        vector<bool> visited(n+1, false);
        priority_queue<Node> que;
        for (vector<int> &t : times)
        {
            graph[t[0]].push_back(Edge(t[1], t[2]));
        }

        dist[K] = 0;
        que.push(Node(K, 0));
        
        while (!que.empty())
        {
            Node temp = que.top();
            que.pop();
            if (visited[temp.id]) continue;
            visited[temp.id] = true;
            for (Edge& item: graph[temp.id])
            {
                if (!visited[item.point] && dist[item.point] > dist[temp.id] + item.cost)
                {
                    dist[item.point] = dist[temp.id] + item.cost;
                    que.push(Node(item.point, dist[item.point]));
                }
            }
        }

        int ans = 0;
        for (int i = 1; i <= n; i++) ans = max(ans, dist[i]);

        return ans == INF ? -1 : ans;
    }
};
