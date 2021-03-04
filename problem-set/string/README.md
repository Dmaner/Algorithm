# 字符串

## 经典算法

- KMP算法

前缀函数`π(i)`

定义为数组`s[0,....,i]`真前缀和真后缀相等的最大长度

```c++
vector<int> prefix_function(string s) {
  int n = (int)s.length();
  vector<int> pi(n);
  for (int i = 1; i < n; i++)
    for (int len = i; len >= 0; len--)
      if (s.substr(0, len) == s.substr(i - len + 1, len)) 
      {
        pi[i] = j;
        break;
      }
  return pi;
}
```

优化一:

对于`π[i + 1]`，如果`s[i + 1]`和`s[π[i]]`相等则`π[i + 1] = π[i] + 1`

```c++
vector<int> prefix_function(string s) {
  int n = (int)s.length();
  vector<int> pi(n);
  for (int i = 1; i < n; i++)
    for (int len = pi[i-1] + 1; len >= 0; len--)
      if (s.substr(0, len) == s.substr(i - len + 1, len)) 
      {
        pi[i] = j;
        break;
      }
  return pi;
}
```

优化二：

对于优化一，`s[i+1]`和`s[π[i]]`不等时，则查找第二个长度`len`不小于`π[i]`测试`s[i+1]`和`s[j]`是否相等，因为`len`必然是存在于`π[i]`长度的前缀或者为0，即`s[0,...,len-1] == s[i - len + 1, ..., i] == s[π[i] - len, ..., π[i]-1]`，结合定义观察可发现`len = π[π[i] - 1]`

```c++
vector<int> prefix_function(string s) {
  int n = (int)s.length();
  vector<int> pi(n);
  for (int i = 1; i < n; i++) 
  {
    int len = pi[i - 1];
    while (len > 0 && s[i] != s[len]) j = pi[len - 1];
    if (s[i] == s[len]) len++;
    pi[i] = len;
  }
  return pi;
}
```

前缀函数的应用-KMP

例题: LeetCode 28 实现strStr()

```c++
class Solution {
public:
    vector<int> prefuc(string &needle)
    {
        int n = needle.length();
        vector<int> pi(n);
        for (int i = 1; i < n; i++)
        {
            int len = pi[i - 1];
            while (len > 0 && needle[len] != needle[i]) len = pi[len - 1];
            if (needle[i] == needle[len]) len ++;
            pi[i] = len;
        }
        return pi;
    }
    int strStr(string haystack, string needle) {
        if (needle.empty()) return 0;
        int len = 0;
        int n = needle.length();
        vector<int> pi = prefuc(needle);
        for (int i = 0; i < haystack.size(); i++)
        {
            while (len > 0 && needle[len] != haystack[i]) len = pi[len - 1];
            if (haystack[i] == needle[len]) len ++;
            if (n == len) return i - len + 1;
        }
        return -1;
    }
};
``` 

## 经典例题

LeetCode 151  翻转字符串里的单词

```c++
class Solution {
public:
    void func(string &s, int l, int r)
    {
        for (int i = l, j = r; i < j; i++, j--)
        {
            swap(s[i], s[j]);
        }
    }
    string reverseWords(string s) {
        int n = s.length();
        func(s, 0, n-1);
        int idx = 0;
        for (int i = 0; i < n; i++)
        {
            if (s[i] == ' ') continue;

            // 不是第一个空格，跳转到下一个放单词的位置
            if (idx != 0) s[idx ++ ] = ' ';
            int start = idx;

            int j = i;
            while (j < n && s[j] != ' ') s[idx++] = s[j++];

            reverse(s.begin() + start, s.begin() + idx);
            i = j;
        }
        s.erase(idx, n);
        return s;
    }
};
```