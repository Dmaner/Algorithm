#include <vector>
#include <string>

using namespace std;

class Solution
{
public:
    bool canConstruct(string s, int k)
    {
        vector<int> charVec(26);
        for (auto it : s)
        {
            charVec[it - 'a']++;
        }
        int oddCnt = 0;
        for (auto it : charVec)
        {
            if (it & 1)
            {
                oddCnt++;
            }
        }
        return (oddCnt <= k && k <= s.size());
    }
};