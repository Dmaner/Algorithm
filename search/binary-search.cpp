#include<iostream>
#include<bits/stdc++.h>

using namespace std;

int binarysearch(vector<int> a, int value){
    // find the first value bigger than value
    int left = 0;
    int right = a.size();
    while (left < right)
    {
        int mid = left + (right - left) / 2;
        if (a[mid] < value) left = mid+1;
        else right = mid;
    }
    cout << left << endl;
    return a[left];
}

int binarysearch2(vector<int> a, int value){
    // find the last value smaller than value
    int left = 0;
    int right = a.size();
    while (left < right)
    {
        int mid = left + (right - left) / 2;
        if (a[mid] < value) left = mid+1;
        else right = mid-1;
    }
    return a[left];
}

int main()
{
    vector<int> a = {1,2,3,4,5,6,7,8,9};
    cout << binarysearch(a, 10) << endl;
    return 0;
}
