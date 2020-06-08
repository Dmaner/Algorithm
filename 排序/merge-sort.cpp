#include<iostream>
#include<bits/stdc++.h>

using namespace std;

void Merge(int arr[], int left, int mid, int right){
    int len_1 = mid - left + 1;
    int len_2 = right - mid;
    
    int *a = new int[len_1];
    int *b = new int[len_2];
    
    for (int i = 0;i < len_1; i++) a[i] = arr[i+left];
    for (int i = 0;i < len_2; i++) b[i] = arr[i+mid+1];
    int i = 0, j = 0;
    while(i < len_1 && j < len_2){
        if (a[i] < b[j]){
            arr[left++] = a[i++]; 
        }
        else{
            arr[left++] = b[j++];
        }
    }
    while (i < len_1) arr[left++] = a[i++];
    while (j < len_2) arr[left++] = b[j++];

    delete []a;
    delete []b;
}

void Merge_sort(int a[], int left, int right){
    if (left < right){
        int mid = (left + right) / 2;
        Merge_sort(a, left, mid);
        Merge_sort(a, mid+1, right);
        Merge(a, left, mid, right);
    }
}

int main(){
    int array[]={34,65,12,43,67,5,78,10,3,70},k;
	int len=sizeof(array)/sizeof(int);
	cout<<"The orginal arrayare:"<<endl;
	for(k=0;k<len;k++)
		cout<<array[k]<<", ";
	cout<<endl;
	Merge_sort(array,0,len-1);
	cout<<"The sorted arrayare:"<<endl;
	for(k=0;k<len;k++)
		cout<<array[k]<<", ";
	cout<<endl;
	return 0;
}