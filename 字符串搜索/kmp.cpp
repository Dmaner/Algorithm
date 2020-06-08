#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int *createNext(string &sub)
{
    int *next = new int[sub.size()]; 
    int i = 0, j = next[0] = -1;     
    while (i < sub.size() - 1)
    { 
        if (j < 0 || sub[i] == sub[j])
        {
            i++;
            j++;
            next[i] = (sub[i] == sub[j] ? next[j] : j); 
        }
        else
        {
            j = next[j];
        }
    }
    return next;
}
int kmp(string &s, string &sub)
{
    int *next = createNext(sub);
    int i = 0, j = 0;
    while (i < (int)s.size() && j < (int)sub.size())
    { 
        if (j < 0 || s[i] == sub[j])
        {
            i++;
            j++;
        }
        else
        {
            j = next[j];
        }
    }
    delete[] next; 
    if (j >= sub.size())
        return i - j; 
    return -1;        
}

int main(int argc, char const *argv[])
{
    string p1 = "nihaodmanasas";
    string p2 = "dman";
    ios::sync_with_stdio(false);
    cout << kmp(p1, p2) << endl;
    return 0;
}
