// leetcode 5 link: https://leetcode-cn.com/problems/longest-palindromic-substring/
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    // 使用动态规划
    string longestPalindrome(string s)
    {
        int length = s.length();
        bool dp[length][length];
        string ans;
        memset(dp, false, sizeof(dp));
        for (int i = 0; i < length; i++)
        {
            for (int left = 0, right = i; right < length; left++, right++)
            {
                if (i == 0)
                    dp[left][right] = true;
                else if (i == 1)
                    dp[left][right] = s[left] == s[right];
                else
                    dp[left][right] = (s[left] == s[right]) && dp[left + 1][right - 1];
                if (dp[left][right] && ans.length() < right - left + 1)
                    ans = s.substr(left, right - left + 1);
            }
        }
        return ans;
    }

    // 中心扩展算法
    pair<int, int> expandcenter(const string &s, int left, int right)
    {
        while (left >= 0 && right < s.length() && s[left] == s[right])
            left--, right++;
        return {left + 1, right - 1};
    }
    string longestPalindrome2(string s)
    {
        string ans;
        for (int i = 0; i < s.length(); i++)
        {
            auto one = expandcenter(s, i, i);
            auto two = expandcenter(s, i, i + 1);
            if (ans.length() < one.second - one.first + 1)
                ans = s.substr(one.first, one.second - one.first + 1);
            if (ans.length() < two.second - two.first + 1)
                ans = s.substr(two.first, two.second - two.first + 1);
        }
        return ans;
    }

    // manacher算法
    string longestPalindrome3(string s)
    {
        int n = s.length();
        if (n < 2)
            return s;

        string temp = "*";
        for (auto &c : s)
            temp += c, temp += '*';

        n = 2 * n + 1;
        // 记录臂展长度
        vector<int> dp(n);

        // 最大的中心点
        int maxright = 0;
        int center = 0;
        int maxLen = 1;
        int start = 0;

        for (int i = 0; i < n; i++)
        {
            if (i < maxright)
            {
                int mirror = 2 * center - i;
                dp[i] = min(dp[mirror], maxright - i);
            }

            // 计算i点臂展
            int left = i - dp[i] - 1;
            int right = i + dp[i] + 1;
            while (left >= 0 && right < n && temp[left] == temp[right])
                dp[i]++, left--, right++;
            if (i + dp[i] > maxright)
                maxright = i + dp[i], center = i;
            if (dp[i] > maxLen)
                maxLen = dp[i], start = (i - maxLen) / 2;
        }
        return s.substr(start, maxLen);
    }
};

int main(int argc, char const *argv[])
{
    string case1 = "babad";
    Solution s;
    cout << s.longestPalindrome3(case1) << endl;
    return 0;
}
