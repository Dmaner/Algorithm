// leetcode 684 link: https://leetcode-cn.com/problems/redundant-connection/
#include <bits/stdc++.h>

#include <iostream>

using namespace std;

class Union_Find {
 private:
  vector<int> pre, size;

 public:
  Union_Find(int n) : pre(n), size(n, 1) { iota(pre.begin(), pre.end(), 0); }

  int find(int x) {
    int r = x, rec = x;
    while (r != pre[r]) r = pre[r];
    // compress path
    while (rec != r) {
      int p = pre[rec];
      pre[rec] = r;
      rec = p;
    }
    return r;
  }
  void connect(int x, int y) {
    int r_x = pre[x];
    int r_y = pre[y];
    if (r_x != r_y) {
      // merge by set's size
      if (size[r_x] < size[r_y]) {
        pre[r_x] = r_y;
        size[r_y] += size[r_x];
      } else {
        pre[r_y] = r_x;
        size[r_x] += size[r_y];
      }
    }
  }

  bool isconnected(int x, int y) { return find(x) == find(y); }
};

class Solution {
 public:
  vector<int> findRedundantConnection(vector<vector<int>>& edges) {
    int n = edges.size();
    Union_Find uf(n + 1);
    for (auto& edge : edges) {
      if (uf.isconnected(edge[0], edge[1]))
        return edge;
      else
        (uf.connect(edge[0], edge[1]));
    }
    return {};
  }
};