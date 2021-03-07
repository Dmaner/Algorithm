# 排序

## 经典算法

- 快速排序

```c++
void quicksort(int a[], int l, int r)
{
    int i = l, j = r, number = a[i];
    if (i >= j)
        return;
    while (i < j)
    {
        while (i < j && a[j] >= number)
            j--;
        if (i < j)
            a[i++] = a[j];
        while (i < j && a[i] < number)
            i++;
        if (i < j)
            a[j--] = a[i];
    }
    a[i] = number;
    quicksort(a, l, i - 1);
    quicksort(a, i + 1, r);
}
```

- 归并排序

```c++
void Merge(int arr[], int left, int mid, int right)
{
    int len_1 = mid - left + 1;
    int len_2 = right - mid;

    int *a = new int[len_1];
    int *b = new int[len_2];

    for (int i = 0; i < len_1; i++)
        a[i] = arr[i + left];
    for (int i = 0; i < len_2; i++)
        b[i] = arr[i + mid + 1];
    int i = 0, j = 0;
    while (i < len_1 && j < len_2)
    {
        if (a[i] < b[j])
        {
            arr[left++] = a[i++];
        }
        else
        {
            arr[left++] = b[j++];
        }
    }
    while (i < len_1)
        arr[left++] = a[i++];
    while (j < len_2)
        arr[left++] = b[j++];

    delete[] a;
    delete[] b;
}

void Merge_sort(int a[], int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;
        Merge_sort(a, left, mid);
        Merge_sort(a, mid + 1, right);
        Merge(a, left, mid, right);
    }
}x  
```

- 堆排序

- 建堆时间O(n)，排序时间O(nlogn)

```c++
int parent(int i)
{
    return (i - 1) / 2;
}

int left(int i)
{
    return 2 * i + 1;
}

int right(int i)
{
    return 2 * i + 2;
}

void swap(int &num1, int &num2)
{
    int temp = num1;
    num1 = num2;
    num2 = temp;
}

void max_heapify(int *nums, int i, int heapsize)
{
    int l = left(i);
    int r = right(i);
    int largest;
    if (l < heapsize && nums[l] > nums[i])
        largest = l;
    else
        largest = i;

    if (r < heapsize && nums[r] > nums[largest])
        largest = r;

    if (largest != i)
    {
        swap(nums[i], nums[largest]);
        max_heapify(nums, largest, heapsize);
    }
}

void build_max_heap(int *nums, int heapsize)
{
    for (int i = heapsize / 2; i >= 0; i--)
        max_heapify(nums, i, heapsize);
}

void heapsort(int *nums, int length)
{
    int heapsize = length;
    build_max_heap(nums, heapsize);
    for (int i = length - 1; i > 0; i--)
    {
        swap(nums[i], nums[0]);
        --heapsize;
        max_heapify(nums, 0, heapsize);
    }
}
```

## 经典例题

LeetCode 215. 数组中的第K个最大元素

```c++
class Solution {
public:
    int qucfunc(vector<int>& nums, int l, int r)
    {
        int temp = nums[l];
        while (l < r)
        {
            while (l < r && temp >= nums[r])
            {
                r --;
            }
            if (l < r) nums[l++] = nums[r];
            while (l < r && temp < nums[l])
            {
                l ++;
            }
            if (l < r) nums[r--] = nums[l];
        }
        nums[l] = temp;
        return l;
    }
    int findKthLargest(vector<int>& nums, int k) {
        int n = nums.size();
        int i = 0; 
        int j = n - 1;
        while (i < j)
        {
            int index = qucfunc(nums, i, j);
            if (index == k - 1) return nums[index];
            else if (index < k - 1) i = index + 1;
            else j = index - 1;
        }
        return nums[i];
    }
};
```