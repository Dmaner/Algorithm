# 图

### 经典例题

- 拓扑排序

LeetCode 210 课程表

```c++
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> indegree(numCourses, 0);
        vector<vector<int>> graph(numCourses, vector<int>());
        for (auto item : prerequisites)
        {
            graph[item[1]].push_back(item[0]);
            indegree[item[0]] ++;
        }
        queue<int> course;
        for (int i = 0; i < numCourses; i++)
        {
            if (!indegree[i]) course.push(i);
        }
        while (!course.empty())
        {
            int item = course.front();
            course.pop();
            numCourses --;
            for (auto next : graph[item])
            {
                if (!--indegree[next])
                {
                    course.push(next);
                }
            }
        }
        return numCourses == 0 ? true : false;
    }
};
```

LeetCode 1203 项目管理

```c++
class Solution
{
  public:
    vector<int> topSort(vector<int> &degree, vector<vector<int>> &graph, vector<int> &items)
    {
        queue<int> q;
        vector<int> ans;
        for (int item : items)
        {
            if (!degree[item])
                q.push(item);
        }
        while (!q.empty())
        {
            int item = q.front();
            q.pop();
            ans.push_back(item);
            for (int next : graph[item])
            {
                if (!--degree[next])
                {
                    q.push(next);
                }
            }
        }
        return ans.size() == items.size() ? ans : vector<int>();
    }

    vector<int> sortItems(int n, int m, vector<int> &group, vector<vector<int>> &beforeItems)
    {
        // <groud id, list<item>>
        vector<vector<int>> group2item(n + m);

        // <id, item>
        vector<int> id2item(n+m);

        // group map & degree
        vector<vector<int>> groupgraph(n + m);
        vector<int> groupdegree(n + m, 0);

        // item map & degree
        vector<vector<int>> itemgraph(n);
        vector<int> itemdegree(n, 0);

        for (int i = 0; i < n + m; i++)
        {
            id2item[i] = i;
        }

        // add id to non-group item
        int fakeId = m;
        for (int i = 0; i < n; i++)
        {
            if (group[i] == -1)
            {
                group[i] = fakeId++;
            }

            // add item to group
            group2item[group[i]].emplace_back(i);
        }

        // build group graph
        for (int i = 0; i < n; i++)
        {
            int curgroup = group[i];
            for (auto &item : beforeItems[i])
            {
                int beforegroup = group[item];
                // item & before item both in the same group
                if (beforegroup == curgroup)
                {
                    itemdegree[i]++;
                    itemgraph[item].emplace_back(i);
                }
                else
                {
                    groupdegree[curgroup]++;
                    groupgraph[beforegroup].emplace_back(curgroup);
                }
            }
        }

        // 组间排序
        vector<int> resg = topSort(groupdegree, groupgraph, id2item);
        if (resg.size() == 0)
            return vector<int>();

        vector<int> ans;
        // 组内排序
        for (int &groupid : resg)
        {
            int size = group2item[groupid].size();
            if (size == 0)
                continue;

            vector<int> res = topSort(itemdegree, itemgraph, group2item[groupid]);
            if (res.size() == 0)
                return vector<int>();

            for (auto &item : res)
            {
                ans.emplace_back(item);
            }
        }
        return ans;
    }
};
```

- 最短路径

LeetCode 743 网络延迟时间

```c++
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
```

LeetCode 332 重新安排行程

```c++

```

## 其他例题

LeetCode 332 重新安排行程