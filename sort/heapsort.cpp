#include<iostream>
#include<bits/stdc++.h>

int parent(int i){
    return (i-1)/2;
}

int left(int i){
    return 2*i+1;
}

int right(int i){
    return 2*i+2;
}

void swap(int &num1, int &num2){
    int temp = num1;
    num1 = num2;
    num2 = temp;
}

void max_heapify(int *nums, int i, int heapsize){
    int l = left(i);
    int r = right(i);
    int largest;
    if (l < heapsize && nums[l] > nums[i])
        largest = l;
    else
        largest = i;

    if (r < heapsize && nums[r] > nums[largest])
        largest = r;

    if (largest != i){
        swap(nums[i], nums[largest]);
        max_heapify(nums, largest, heapsize);
    }
}

void build_max_heap(int* nums, int heapsize){
    for (int i = heapsize/2;i >= 0; i--)
        max_heapify(nums, i, heapsize);
}

void heapsort(int* nums, int length){
    int heapsize = length;
    build_max_heap(nums, heapsize);
    for (int i = length-1; i > 0; i--)
    {
        swap(nums[i], nums[0]);
        --heapsize;
        max_heapify(nums, 0, heapsize);
    }
}

int main(int argc, char const *argv[])
{
    
    int a[10] = {9,8,7,6,5,4,3,2,1};
    heapsort(a, 10);
    for (int num: a)
    {
        std::cout << num << " ";
    }
    
    return 0;
}
