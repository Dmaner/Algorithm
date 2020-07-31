// leetcode-518
// link: https://leetcode-cn.com/problems/coin-change-2/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int change(int amount, vector<int>& coins) {
        int n = coins.size();
        vector<int> dp(amount+1, 0);
        dp[0] = 1;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 0; j <= amount; j++)
            {
                if (j - coins[i-1] >= 0) dp[j] += dp[j-coins[i-1]];
            }
        }
        return dp[amount];
    }
};

int main(int argc, char const *argv[])
{
    Solution s;
    int amount = 5;
    vector<int> coins{1, 2, 5};
    cout << s.change(amount, coins) << endl;
    return 0;
}
