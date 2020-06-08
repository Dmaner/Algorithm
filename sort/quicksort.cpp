#include<iostream>

using namespace std;

void quicksort(int a[], int l, int r){
    int i = l, j = r, number = a[i];
    if (i >= j) return;
    while (i < j)
    {
        while (i < j && a[j] >= number) j--;
        if (i < j) a[i++] = a[j];
        while (i < j && a[i] < number) i++;
        if (i < j) a[j--] = a[i];
    }
    a[i] = number;
    quicksort(a, l, i-1);
    quicksort(a, i+1, r);
}

int main()
{
    int array[]={34,65,12,43,67,5,78,10,3,70},k;
	int len=sizeof(array)/sizeof(int);
	cout<<"The orginal arrayare:"<<endl;
	for(k=0;k<len;k++)
		cout<<array[k]<<", ";
	cout<<endl;
	quicksort(array,0,len-1);
	cout<<"The sorted arrayare:"<<endl;
	for(k=0;k<len;k++)
		cout<<array[k]<<", ";
	cout<<endl;
	return 0;
}
