// Leetcode-417
// problem link: https://leetcode-cn.com/problems/partition-equal-subset-sum/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  bool canPartition(vector<int>& nums) {
    int n = nums.size();
    int sum = 0;
    for (int num : nums) sum += num;
    if (sum % 2 != 0) return false;
    sum /= 2;
    vector<bool> dp(sum+1, false);
    // initial
    dp[0] = true;
    
    for (int i = 1; i <= n; ++i)
    {
        for (int j = sum; j >= 0; --j)
        {
            if (j - nums[i-1] >= 0) dp[j] = dp[j] || dp[j-nums[i-1]];
        }
    }
    return dp[sum];
  }
};

int main(int argc, char const* argv[]) {
  Solution s;
  vector<int> nums{1, 5, 11, 5};
  cout << boolalpha << s.canPartition(nums) << endl;
  return 0;
}
