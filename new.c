#include<stdio.h>

int ccount = 0;

void swap(int *arr, int i, int j)
{
    int n = arr[j];
    arr[j] = arr[i];
    arr[i] = n;
}
void quick(int *arr, int l, int r)
{
    if (l < r)
    {
        int max = arr[r];
        int i = l - 1;
        for (int j = l; j <= r - 1; j++)
        {
            ccount++;
            if (arr[j] < max)
            {
                i++;
                swap(arr, i, j);
            }
        }
        swap(arr, i + 1, r);
        int pivot = i + 1;
        quick(arr, l, pivot - 1);
        quick(arr, pivot + 1, r);
    }
}
void quick_sort(int arr[], int l, int r)
{
    ccount = 0;
    quick(arr, l, r);
}

int main(){
    int arr[]={5,4,3,2,1};
    quick_sort(arr,0,4);
    printf("%d",ccount);
    return 0;
}