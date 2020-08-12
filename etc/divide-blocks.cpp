// give int a, b return sum = a/1 + a/2 + a/3 + ... + a/b
#include <bits/stdc++.h>

using namespace std;

int fuc(int a, int b) {
  int ans = 0;
  for (int l = 1, r; l <= min(a, b); l = r + 1) {
    r = a / (a / l);
    ans += (a / l) * (r - l + 1);
  }
  return ans;
}