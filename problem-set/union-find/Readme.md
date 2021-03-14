# 并查集

## 使用思路

- 联通分量个数
- 冗余连接
- 棋盘类，得到联通性

## 经典例题

### [LeetCode 547 省份数量](https://leetcode-cn.com/problems/number-of-provinces/)

- 思路：并查集
- 代码

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

### [LeetCode 721 账户合并](https://leetcode-cn.com/problems/accounts-merge/)

- 思路：哈希表+并查集，将邮件序列化
- 代码

```c++
class UnionFind {
    private:
        vector<int> f, sz;
    public:
        UnionFind(int n) : f(n), sz(n, 1)
        {
            iota(f.begin(), f.end(), 0);
        }
        int find(int x)
        {
            return f[x] == x ? x : f[x] = find(f[x]);
        }
        void merge(int x, int y)
        {
            x = find(x);
            y = find(y);
            if (x == y) return;
            if (sz[x] < sz[y]) swap(x, y);
            f[y] = x;
            sz[x] += sz[y];
        }
};

class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        unordered_map<string, int> m2idx;
        unordered_map<string, string> m2name;
        int count = 0;

        // init
        for (auto& item : accounts)
        {
            string name = item[0];
            for (int i = 1; i < item.size(); i++)
            {
                string m = item[i];
                if (!m2idx.count(m))
                {
                    m2idx[m] = count ++;
                    m2name[m] = name;
                }
            }
        }
        
        UnionFind uf(count);
        // merge
        for (auto& item : accounts)
        {
            int first = m2idx[item[1]];
            for (int i = 2; i < item.size(); i++)
            {
                int sec = m2idx[item[i]];
                uf.merge(sec, first);
            }
        }

        unordered_map<int, vector<string>> idx2ms;
        for (auto& item : m2idx)
        {
            int root = uf.find(item.second);
            idx2ms[root].push_back(item.first);
        }

        vector<vector<string>> ans;
        for (auto& item : idx2ms)
        {
            auto ms = item.second;
            int root = item.first;
            sort(ms.begin(), ms.end());
            string name = m2name[ms[0]];
            vector<string> newacc;
            newacc.push_back(name);
            for (string& s : ms)
            {
                newacc.push_back(s);
            }
            ans.push_back(newacc);
        }

        return ans;
    }
};
```



### [LeetCode 684 冗余连接](https://leetcode-cn.com/problems/redundant-connection/)

- 思路：并查集合并连通分量，直到查询到相同的连通分量

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

### [Leetcode 1202  交换字符串中的元素](https://leetcode-cn.com/problems/smallest-string-with-swaps/)

- 大致题意

给定n个数，给定一个交换序列，每次交换两个元素，求最小字典序

- 思路

用并查集确定连通分量，然后用一个`hashmap`存储根节点对应同一连通分量的数组，然后从小到大遍历`hashmap`对对应的连通分量进行排序然后进行总的合并

- 代码

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
```

### [LeetCode 947 移除最多的同行或同列石头](https://leetcode-cn.com/problems/most-stones-removed-with-same-row-or-column/)

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
### [LeetCode 803 打砖块](https://leetcode-cn.com/problems/bricks-falling-when-hit/submissions/)

- 思路

并查集+逆向思考，先得到打完之后做并查集，然后逆序合并，记录一次合并完后的符合条件的连通分量增加量

- 代码

```c++
class UnionFind
{
  private:
    vector<int> f;
    vector<int> sz;

  public:
    UnionFind(int n) : f(n), sz(n, 1)
    {
        iota(f.begin(), f.end(), 0);
    }
    int find(int x)
    {
        return f[x] == x ? x : f[x] = find(f[x]);
    }
    void merge(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x == y)
            return;
        if (sz[x] < sz[y])
            swap(x, y);
        f[y] = x;
        sz[x] += sz[y];
    }
    int size(int x)
    {
        return sz[find(x)];
    }
};

class Solution
{
  private:
    int h, w;
    const vector<int> d = {-1, 0, 1, 0, -1};

  public:
    inline int check(int x, int y)
    {
        if (x >= 0 && x < h && y >= 0 && y < w)
        {
            return true;
        }
        return false;
    }
    inline int getpos(int x, int y)
    {
        return x * w + y;
    }
    vector<int> hitBricks(vector<vector<int>> &grid, vector<vector<int>> &hits)
    {
        h = grid.size();
        w = grid[0].size();
        vector<vector<int>> copy = grid;
        UnionFind uf(h * w + 1);

        for (auto hit : hits)
        {
            copy[hit[0]][hit[1]] = 0;
        }

        // merge stable
        for (int i = 0; i < h; i++)
        {
            for (int j = 0; j < w; j++)
            {
                if (!copy[i][j]) continue;
                int pos = getpos(i, j);
                if (i == 0)
                    uf.merge(h * w, pos);
                if (i > 0 && copy[i - 1][j] == 1)
                    uf.merge(getpos(i - 1, j), pos);
                if (j > 0 && copy[i][j - 1] == 1)
                    uf.merge(getpos(i, j - 1), pos);
            }
        }

        vector<int> ans(hits.size());

        for (int i = hits.size() - 1; i >= 0; i--)
        {
            int pre = uf.size(h * w);
            int x = hits[i][0];
            int y = hits[i][1];
            if (grid[x][y] == 0) continue;
            if (x == 0)
            {
                uf.merge(h * w, y);
            }

            for (int i = 0; i < 4; i++)
            {
                int r = x + d[i];
                int c = y + d[i + 1];
                if (check(r, c) && copy[r][c] == 1)
                {
                    uf.merge(getpos(r, c), getpos(x, y));
                }
            }
            int cur = uf.size(h * w);
            ans[i] = max(0, cur - pre - 1);
            copy[x][y] = 1;
        }
        return ans;
    }
};
```

## 其他例题

- LeetCode 399 除法求值