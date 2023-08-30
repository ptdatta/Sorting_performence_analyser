#include <stdio.h>
#include <stdlib.h>

// For debugging purposes
void display(int arr[], int size)
{
    for (int i = 0; i < size; i++)
        printf("%d, ", arr[i]);
    printf("\n");
}

// Returns a memory copy of an array
int *duplicate_array(int arr_orig[], int size)
{
    int *arr_copy = malloc(sizeof(int) * size);

    if (arr_copy == NULL)
    {
        fprintf(stderr, "Failed to allocate duplicate of size %lu bytes.\n", sizeof(int) * size);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; i++)
        arr_copy[i] = arr_orig[i];
    return arr_copy;
}

void swap(int *arr, int i, int j)
{
    int n = arr[j];
    arr[j] = arr[i];
    arr[i] = n;
}

// Comparison count for each of the algorithms
// is updated whenever a comparison is made, regardless
// of whether that resulted in a swap.
unsigned long ccount;

// TODO: Implement the following, taking care to
//       update `ccount` as appropriate.
void select_sort(int arr[], int l, int r)
{
    ccount = 0;
    for (int i = l; i <= r; i++)
    {
        int max = l;
        int last = r - i;
        for (int j = l + 1; j <= last; j++)
        {
            ccount++;
            if (arr[max] < arr[j])
            {
                max = j;
            }
        }
        swap(arr, max, last);
    }
}

void bubble_sort(int arr[], int l, int r)
{
    ccount = 0;
    int sort = 1;
    for (int i = l; i <= r; i++)
    {
        sort = 1;
        for (int j = 1; j <= r - i; j++)
        {
            if (arr[j] < arr[j - 1])
            {
                swap(arr, j - 1, j);
                sort = 0;
            }
            ccount++;
        }
        if (sort == 1)
            break;
    }
}

void insert_sort(int arr[], int l, int r)
{
    ccount = 0;
    for (int i = l + 1; i <= r; i++)
    {
        int key = arr[i];
        int j;
        int c = 0;
        for (j = i - 1; j >= 0 && arr[j] > key; j--)
        {
            ccount++;
            arr[j + 1] = arr[j];
            c = 1;
        }
        if (c == 0)
        {
            ccount++;
        }
        arr[j + 1] = key;
    }
}

void merge(int *arr, int l, int r)
{
    int m = l + (r - l) / 2;
    if (r > l)
    {
        merge(arr, l, m);
        merge(arr, m + 1, r);
        int n1 = m - l + 1;
        int n2 = r - m;
        int L[n1], R[n2];
        for (int i = 0; i < n1; i++)
            L[i] = arr[l + i];
        for (int j = 0; j < n2; j++)
            R[j] = arr[m + 1 + j];
        int i = 0, j = 0, k = l;
        while (i < n1 && j < n2)
        {
            ccount++;
            if (L[i] <= R[j])
            {
                arr[k] = L[i];
                i++;
            }
            else
            {
                arr[k] = R[j];
                j++;
            }
            k++;
        }
        while (i < n1)
        {
            arr[k] = L[i];
            i++;
            k++;
        }
        while (j < n2)
        {
            arr[k] = R[j];
            j++;
            k++;
        }
    }
}
void merge_sort(int arr[], int l, int r)
{
    ccount = 0;
    merge(arr, l, r);
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

int main(int argc, char **argv)
{
    if (argc != 6)
    {
        fprintf(stderr, "Usage:\n%s [INPUT SIZE] [INPUT FILE] [ASCENDING INPUT FILE] [DESCENDING INPUT FILE] [OUTPUT STATS CSV]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int size = 0;
    if (sscanf(argv[1], "%d", &size) != 1 || size < 0)
    {
        fprintf(stderr, "Invalid size supplied.\n");
        exit(EXIT_FAILURE);
    }

    int *arr = malloc(sizeof(int) * size);
    int *arrasc = malloc(sizeof(int) * size);
    int *arrdes = malloc(sizeof(int) * size);
    if (arr == NULL || arrasc == NULL || arrdes == NULL)
    {
        fprintf(stderr, "Failed to allocate array of size %lu bytes.\n", sizeof(int) * size);
        exit(EXIT_FAILURE);
    }

    FILE *fin = fopen(argv[2], "r");
    FILE *finasc = fopen(argv[3], "r");
    FILE *findes = fopen(argv[4], "r");
    if (fin == NULL || finasc == NULL || findes == NULL)
    {
        fprintf(stderr, "Could not open %s\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    // Input file has each integer on a new line
    for (int i = 0; i < size; i++)
    {
        fscanf(fin, "%d", arr + i);
        fscanf(finasc, "%d", arrasc + i);
        fscanf(findes, "%d", arrdes + i);
    }

    fclose(fin);
    fclose(finasc);
    fclose(findes);

    // Output file format:
    // sort_algo,input_size,num_comparisons
    FILE *fout = fopen(argv[5], "a");

    int *arr_copy;
    int *arrasc_copy;
    int *arrdes_copy;

    // Selection Sort
    arr_copy = duplicate_array(arr, size);
    arrasc_copy = duplicate_array(arrasc, size);
    arrdes_copy = duplicate_array(arrdes, size);
    ccount = 0;
    select_sort(arr_copy, 0, size - 1);
    fprintf(fout, "%s,%d,%lu\n", "select", size, ccount);
    select_sort(arrasc_copy, 0, size - 1);
    fprintf(fout, "%s,%d,%lu\n", "select", size, ccount);
    select_sort(arrdes_copy, 0, size - 1);
    fprintf(fout, "%s,%d,%lu\n", "select", size, ccount);
    free(arr_copy);
    free(arrasc_copy);
    free(arrdes_copy);

    // Bubble Sort
    arr_copy = duplicate_array(arr, size);
    arrasc_copy = duplicate_array(arrasc, size);
    arrdes_copy = duplicate_array(arrdes, size);
    ccount = 0;
    bubble_sort(arr_copy, 0, size - 1);
    fprintf(fout, "%s,%d,%lu\n", "bubble", size, ccount);
    bubble_sort(arrasc_copy, 0, size - 1);
    fprintf(fout, "%s,%d,%lu\n", "bubble", size, ccount);
    bubble_sort(arrdes_copy, 0, size - 1);
    fprintf(fout, "%s,%d,%lu\n", "bubble", size, ccount);
    free(arr_copy);
    free(arrasc_copy);
    free(arrdes_copy);

    // Insertion Sort
    arr_copy = duplicate_array(arr, size);
    arrasc_copy = duplicate_array(arrasc, size);
    arrdes_copy = duplicate_array(arrdes, size);
    ccount = 0;
    insert_sort(arr_copy, 0, size - 1);
    fprintf(fout, "%s,%d,%lu\n", "insert", size, ccount);
    insert_sort(arrasc_copy, 0, size - 1);
    fprintf(fout, "%s,%d,%lu\n", "insert", size, ccount);
    insert_sort(arrdes_copy, 0, size - 1);
    fprintf(fout, "%s,%d,%lu\n", "insert", size, ccount);
    free(arr_copy);
    free(arrasc_copy);
    free(arrdes_copy);

    // Merge Sort
    arr_copy = duplicate_array(arr, size);
    arrasc_copy = duplicate_array(arrasc, size);
    arrdes_copy = duplicate_array(arrdes, size);
    ccount = 0;
    merge_sort(arr_copy, 0, size - 1);
    fprintf(fout, "%s,%d,%lu\n", "merge", size, ccount);
    merge_sort(arrasc_copy, 0, size - 1);
    fprintf(fout, "%s,%d,%lu\n", "merge", size, ccount);
    merge_sort(arrdes_copy, 0, size - 1);
    fprintf(fout, "%s,%d,%lu\n", "merge", size, ccount);
    free(arr_copy);
    free(arrasc_copy);
    free(arrdes_copy);

    // Quick Sort
    arr_copy = duplicate_array(arr, size);
    arrasc_copy = duplicate_array(arrasc, size);
    arrdes_copy = duplicate_array(arrdes, size);
    ccount = 0;
    quick_sort(arr_copy, 0, size - 1);
    fprintf(fout, "%s,%d,%lu\n", "quick", size, ccount);
    quick_sort(arrasc_copy, 0, size - 1);
    fprintf(fout, "%s,%d,%lu\n", "quick", size, ccount);
    quick_sort(arrdes_copy, 0, size - 1);
    fprintf(fout, "%s,%d,%lu\n", "quick", size, ccount);
    free(arr_copy);
    free(arrasc_copy);
    free(arrdes_copy);

    fclose(fout);
    free(arr);
    free(arrasc);
    free(arrdes);

    return EXIT_SUCCESS;
}
