#include <vector>

using namespace std;

void GroupPack(vector<int> &dp, int V, vector<int> &C, vector<int> &W) {
  for (int i = V; i >= 0; i--) {
    for (int j = 0; j < C.size(); j++) {
      dp[i] = max(dp[i], dp[i - C[i]] + W[i]);
    }
  }
}