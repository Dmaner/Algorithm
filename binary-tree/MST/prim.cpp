#include <bits/stdc++.h>

using namespace std;

const int MAXN = 110;

bool vis[MAXN];
int lowc[MAXN];

int prim(int cost[][MAXN], int n) {
  int ans = 0;
  memset(vis, false, sizeof(vis));
  vis[0] = true;
  for (int i = 1; i < n; i++) lowc[i] = cost[0][i];
  for (int i = 1; i < n; i++) {
    int mincost = INT_MIN;
    int p = -1;
    for (int j = 0; j < n; j++) {
      if (!vis[j] && mincost > lowc[j]) {
        mincost = lowc[j];
        p = j;
      }
    }
    if (mincost == INT_MIN) return -1;
    ans += mincost;
    vis[p] = true;
    for (int j = 0; j < n; j++) {
      if (!vis[j] && lowc[j] > cost[p][j]) lowc[j] = cost[p][j];
    }
  }
  return ans;
}