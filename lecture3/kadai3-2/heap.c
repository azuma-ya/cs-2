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

void heapify(int arr[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i)
    {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heap_sort(int arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--)
    {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

int main(int argc, char *argv[])
{
    char *datafile; // 入力データのファイル名
    FILE *fp;       // 入力データのファイルポインタ
    int n;          // 入力データのデータ数
    int *arr;       // 入力データ格納場所
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
    if (fp == NULL)
    {
        fprintf(stderr, "##### ファイルを開けませんでした\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        if (fscanf(fp, "%d", &arr[i]) != 1)
        {
            fprintf(stderr, "##### ファイルからの読み込みエラー\n");
            fclose(fp);
            free(arr);
            return 1;
        }
    }
    fclose(fp);

    time_start = gettime();
    heap_sort(arr, n);
    time_end = gettime();
    
    for (int i = 0; i < n; i++)
        printf("%d\n", arr[i]);

    fprintf(stderr, "データ数: %d ヒープソートの実行時間 = %lf[秒]\n",n, time_end - time_start);
    
    free(arr);

    return 0;
}