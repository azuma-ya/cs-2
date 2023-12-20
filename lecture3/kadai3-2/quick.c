#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <sys/time.h>

typedef struct timelog
{
    int data_size;
    double time_stamp;
    struct timelog *next;
} timelog;

double gettime()
{
    struct timeval tp;
    double ret;
    gettimeofday(&tp, NULL);
    ret = (double)(tp.tv_sec & 0x00ffffff) + (double)tp.tv_usec / 1000000;
    return ret;
}

void time_stamp(timelog **time_log, int size)
{
    timelog *log = (timelog *)malloc(sizeof(timelog));
    log->data_size = size;
    log->time_stamp = gettime();
    log->next = *time_log;
    *time_log = log;
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high, int interval, timelog **time_log)
{
    for (int i = low; i < high; i++)
    {
        if (arr[i] <= arr[high])
        {
            swap(&arr[low], &arr[i]);
            low++;
        }
        if (i % interval == 0)
            time_stamp(time_log, i);
    }
    swap(&arr[low], &arr[high]);
    return low;
}

void quick_sort(int arr[], int low, int high, int interval, timelog **time_log)
{
    if (low < high)
    {
        int pivot = partition(arr, low, high, interval, time_log);
        quick_sort(arr, low, pivot - 1, interval, time_log);
        quick_sort(arr, pivot + 1, high, interval, time_log);
    }
}

void free_time_log(timelog *time_log)
{
    timelog *log, *next_log;
    for (log = time_log; log != NULL; log = next_log)
    {
        next_log = log->next;
        free(log);
    }
}

int main(int argc, char *argv[])
{
    char *datafile; // 入力データのファイル名
    FILE *fp;       // 入力データのファイルポインタ
    int n;          // 入力データのデータ数
    int *arr;       // 入力データ格納場所
    double time_start;
    timelog *time_log;
    int interval;

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

    if (argc <= 3)
    {
        fprintf(stderr, "##### タイムスタンプ間隔を指定してください\n");
        return 1;
    }
    interval = atoi(argv[3]);

    arr = (int *)malloc(n * sizeof(int));

    fp = fopen(datafile, "r");
    for (int i = 0; i < n; i++)
    {
        fscanf(fp, "%d", &arr[i]);
    }
    fclose(fp);

    time_start = gettime();
    quick_sort(arr, 0, n - 1, interval, &time_log);
    time_stamp(&time_log, n);

    for (timelog *log = time_log; log != NULL; log = log->next)
        fprintf(stderr, "データ数: %d クイックソートの実行時間 = %lf[秒]\n", log->data_size, log->time_stamp - time_start);

    free(arr);
    free_time_log(time_log);

    return 0;
}