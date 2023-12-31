#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <sys/time.h>

double gettime()
{
    struct timeval tp;
    double ret;
    gettimeofday(&tp, NULL);
    ret = (double)(tp.tv_sec & 0x00ffffff) + (double)tp.tv_usec / 1000000;
    return ret;
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high)
{
    for (int i = low; i < high; i++)
    {
        if (arr[i] <= arr[high])
        {
            swap(&arr[low], &arr[i]);
            low++;
        }
    }
    swap(&arr[low], &arr[high]);
    return low;
}

void quick_sort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pivot = partition(arr, low, high);
        quick_sort(arr, low, pivot - 1);
        quick_sort(arr, pivot + 1, high);
    }
}

int main(int argc, char *argv[])
{
    char *datafile; // 入力データのファイル名
    FILE *fp;       // 入力データのファイルポインタ
    int n;          // 入力データのデータ数
    int *arr;       // 入力データ格納場所
    int i;
    double time_start, time_end;

    if (argc <= 1)
    {
        fprintf(stderr, "##### ファイル名を指定してください\n");
        return 1;
    }
    datafile = argv[1];

    if (argc <= 2)
    {
        fprintf(stderr, "##### データ数を指定してください\n");
        return 1;
    }
    n = atoi(argv[2]);

    arr = (int *)malloc(n * sizeof(int));

    fp = fopen(datafile, "r");
    for (int i = 0; i < n; i++)
    {
        fscanf(fp, "%d", &arr[i]);
    }
    fclose(fp);

    time_start = gettime();
    quick_sort(arr, 0, n - 1);
    time_end = gettime();

    fprintf(stderr, "クイックソートの実行時間 = %lf[秒]\n", time_end - time_start);

    for (int i = 0; i < n; i++)
        printf("%d\n", arr[i]);

    free(arr);

    return 0;
}