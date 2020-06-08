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

int maximum(int *nums){
    return nums[0];
}

int heap_extract_max(int *nums, int &heapsize){
    if (heapsize < 1)
        std::cout << "Error" << std::endl;
    int max = nums[0];
    heapsize --;
    nums[0] = nums[heapsize];
    max_heapify(nums, 0, heapsize);
    return max;
}

void heap_increase_key(int* nums, int index, int k){
    // increase value of nums[index]
    if (k < nums[index]) std::cout << "Error" << std::endl;
    nums[index] =k;
    while (index > 0 && nums[parent(index)] < nums[index]){
        swap(nums[index], nums[parent(index)]);
        index = parent(index);
    }
}

void insert(int* nums, int k, int &heapsize){
    heapsize ++;
    nums[heapsize-1] = INT_MIN;
    heap_increase_key(nums, heapsize-1, k);
}


int main(int argc, char const *argv[])
{
    int seq[10] = {9,8,7,6,5,4,3,2,1,0};
    int heapsize = 10;
    std::cout << maximum(seq) << std::endl;
    heap_extract_max(seq, heapsize); // 9
    heap_extract_max(seq, heapsize); // 8
    heap_extract_max(seq, heapsize); // 7
    heap_extract_max(seq, heapsize); // 6
    heap_increase_key(seq, 2, 100);
    insert(seq, 10, heapsize);
    for(int a: seq){
        std::cout << a << " ";
    }
    return 0;
}
