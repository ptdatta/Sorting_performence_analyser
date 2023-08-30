#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void sort(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (arr[i] > arr[j])
            {
                int n = arr[i];
                arr[i] = arr[j];
                arr[j] = n;
            }
        }
    }
}

int main()
{
    for (int i = 0; i < 17; i++)
    {
        int size = pow(2, i);
        int *arr = (int *)calloc(size, sizeof(int));
        FILE *fpr, *fwr1, *fwr2;
        char *str = (char *)calloc(100, sizeof(char));
        sprintf(str, "E:\\collage\\c\\sorting\\resources\\nums2^%d.txt", i);
        fpr = fopen(str, "r");
        for (int j = 0; j < size; j++)
        {
            fscanf(fpr, "%d", &arr[j]);
        }
        sort(arr, size);
        char *str1 = (char *)calloc(100, sizeof(char));
        char *str2 = (char *)calloc(100, sizeof(char));
        sprintf(str1, "E:\\collage\\c\\sorting\\resources\\nums2^%dinc.txt", i);
        sprintf(str2, "E:\\collage\\c\\sorting\\resources\\nums2^%ddec.txt", i);
        fwr1 = fopen(str1, "w");
        fwr2 = fopen(str2, "w");
        for (int j = 0; j < size; j++)
        {
            fprintf(fwr1, "%d\n", arr[j]);
            fprintf(fwr2, "%d\n", arr[size - 1 - j]);
        }
    }
    return 0;
}