// leetcode 940 link: https://leetcode-cn.com/problems/distinct-subsequences-ii

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    int distinctSubseqII(string S)
    {
        long endsWith[26] = {}, mod = 1e9 + 7;
        for (char c : S)
            endsWith[c - 'a'] = accumulate(begin(endsWith), end(endsWith), 1L) % mod;
        return accumulate(begin(endsWith), end(endsWith), 0L) % mod;
    }
};