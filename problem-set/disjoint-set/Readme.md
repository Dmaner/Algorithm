# 并查集

## 并查集

## 经典例题

LeetCode 547 省份数量

```c++
class uf {
    public:
        vector<int> m_parent;
        vector<int> m_size;
        int m_count;
        uf(int n) : m_parent(n), m_count(n), m_size(n, 1)
        {
            iota(m_parent.begin(), m_parent.end(), 0);
        } 
        
        int find(int x)
        {
            return x == m_parent[x] ? x : m_parent[x] = find(m_parent[x]);
        }

        bool unite(int x, int y)
        {
            x = find(x);
            y = find(y);
            if (x == y) return false;
            if (m_size[x] < m_size[y])
            {
                swap(x, y);
            }
            m_parent[y] = x;
            m_size[x] += m_size[y];
            m_count --;
            return true;
        }
};
class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        uf a(n);
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (isConnected[i][j])
                {
                    a.unite(i, j);
                }
            }
        }
        return a.m_count;
    }
};
```

LeetCode 684 冗余连接

```c++
class uf {
public:
    vector<int> parent;
    vector<int> size;
    int count;
    uf(int n) : parent(n), size(n, 1), count(n) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x)
    {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }
    void unite(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x == y) return;
        if (size[x] < size[y]) swap(x, y);
        parent[y] = x;
        size[x] += size[y];
        count --;
    }
    bool isconnected(int x, int y)
    {
        return find(x) == find(y);
    }
};

class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        uf u(n);
        for (auto & edge : edges)
        {
            int x = edge[0] - 1;
            int y = edge[1] - 1;
            if (u.isconnected(x, y)) return edge;
            else u.unite(x, y);
        }
        return vector<int>();
    }
};
```

[**Leetcode 1202**](https://leetcode-cn.com/problems/smallest-string-with-swaps/)

- 代码:

```c++
class DisjointSetUnion {
private:
    vector<int> f, rank;
    int n;

public:
    DisjointSetUnion(int _n) {
        n = _n;
        rank.resize(n, 1);
        f.resize(n);
        for (int i = 0; i < n; i++) {
            f[i] = i;
        }
    }

    int find(int x) {
        return f[x] == x ? x : f[x] = find(f[x]);
    }

    void unionSet(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx == fy) {
            return;
        }
        if (rank[fx] < rank[fy]) {
            swap(fx, fy);
        }
        rank[fx] += rank[fy];
        f[fy] = fx;
    }
};

class Solution {
public:
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
        DisjointSetUnion dsu(s.length());
        for (auto& it : pairs) {
            dsu.unionSet(it[0], it[1]);
        }
        unordered_map<int, vector<int>> mp;
        for (int i = 0; i < s.length(); i++) {
            mp[dsu.find(i)].emplace_back(s[i]);
        }
        for (auto& [x, vec] : mp) {
            sort(vec.begin(), vec.end(), greater<int>());
        }
        for (int i = 0; i < s.length(); i++) {
            int x = dsu.find(i);
            s[i] = mp[x].back();
            mp[x].pop_back();
        }
        return s;
    }
};

[**947. 移除最多的同行或同列石头**](https://leetcode-cn.com/problems/most-stones-removed-with-same-row-or-column/)

- 思路: 对于任意一个连通图，我们总可以通过调整节点的删除顺序，把这个连通图中删到只剩下一个节点，故查找多少联通子图便可

- 代码

```c++
class Solution {
private:
    int n = 20005; // 根据坐标范围而定
    int father[20005];

    // 并查集初始化
    void init() {
        for (int i = 0; i < n; ++i) {
            father[i] = i;
        }
    }
    // 并查集里寻根的过程
    int find(int u) {
        return u == father[u] ? u : father[u] = find(father[u]);
    }
    // 将v->u 这条边加入并查集
    void join(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) return ;
        father[v] = u;
    }
    // 判断 u 和 v是否找到同一个根
    bool same(int u, int v) {
        u = find(u);
        v = find(v);
        return u == v;
    }
public:
    int removeStones(vector<vector<int>>& stones) {
        init();
        for (int i = 0; i < stones.size(); i++) join(stones[i][0], stones[i][1] + 10000);
        unordered_map<int, bool> umap;
        for (int i = 0; i < stones.size(); i++) {
            umap[find(stones[i][0])] = true;
            umap[find(stones[i][1] + 10000)] = true;
        }
        return stones.size() - umap.size();
    }
};

```

```

## 其他例题

- LeetCode 399 除法求值