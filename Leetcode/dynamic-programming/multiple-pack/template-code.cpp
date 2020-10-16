#include <bits/stdc++.h>

#include <iostream>

using namespace std;

void ZeroOnePack(vector<int> &dp, int V, int C, int W) {
  for (int i = V; i >= 0; i--) {
    dp[i] = max(dp[i], dp[i - C] + W);
  }
}

void CompletePack(vector<int> &dp, int V, int C, int W) {
  for (int i = 0; i < V; i++) {
    dp[i] = max(dp[i], dp[i - C] + W);
  }
}

void MultiplePack(vector<int> &dp, int V, int C, int W, int M) {
  if (C * M > V)
    CompletePack(dp, V, C, W);
  else {
    int k = 1;
    while (k < M) {
      ZeroOnePack(dp, V, k * C, k * W);
      M -= k;
      k *= 2;
    }
    ZeroOnePack(dp, V, C * M, W * M);
  }
}

int main(int argc, char const *argv[]) {
  int V, n;
  vector<int> dp(V, 0);
  vector<int> c(n);
  vector<int> w(n);
  vector<int> m(n);
  for (int i = 1; i < V; i++) MultiplePack(dp, V, c[i], w[i], m[i]);
  return 0;
}
