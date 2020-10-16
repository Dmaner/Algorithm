#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Solution {
 public:
  vector<int> diffWaysToCompute(string input) {
    vector<int> ans;
    int n = input.length();
    for (int i = 0; i < n; i++) {
      char c = input[i];
      if (c == '+' || c == '-' || c == '*') {
        vector<int> left = diffWaysToCompute(input.substr(0, i));
        vector<int> right = diffWaysToCompute(input.substr(i + 1));
        for (const int &l : left) {
          for (const int &r : right) {
            switch (c) {
              case '+':
                ans.push_back(l + r);
                break;
              case '-':
                ans.push_back(l - r);
                break;
              case '*':
                ans.push_back(l * r);
                break;
            }
          }
        }
      }
    }
    if (ans.empty()) ans.push_back(stoi(input));
    return ans;
  }
};