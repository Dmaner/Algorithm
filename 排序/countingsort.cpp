#include<iostream>
#include<bits/stdc++.h>

void counting_sort(int* nums, int length, int* sort_nums, int max_num){
    int saves[max_num+1] = {0};
    
    // build nums
    for (int i = 0; i < length; i++)
        saves[nums[i]] ++;

    for (int i = 0; i < max_num;i++){
        saves[i+1] += saves[i];
    }
        
    // sort
    for (int i = 0; i < length;i++){
        int index = saves[nums[i]];
        sort_nums[index-1] = nums[i]; // index - 1 for the index of arr
        saves[index] --;
    }    
}

int main(int argc, char const *argv[])
{
    int a[10] = {1,2,5,3,4,9,6,8,9,10};
    int b[10];
    int length = 10;
    counting_sort(a, 10, b, 10);
    for (int i = 0; i < length; i++)
    {
        std::cout << b[i] << " ";
    }
    return 0;
}
