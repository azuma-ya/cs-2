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

void bucket_sort(int arr[], int n, int buckets[], int under, int interval, timelog **time_log)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i] < under)
            buckets[arr[i]] += 1;
    }

    int k = 0;
    for (int i = 0; i < under; i++)
    {
        for (int j = 0; j < buckets[i]; j++)
        {
            if (k % interval == 0)
                time_stamp(time_log, k);
            arr[k] = i;
            k++;
        }
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
    int *buckets;
    int under;
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

    if (argc <= 3)
    {
        fprintf(stderr, "##### 最大値を指定してください\n");
        return 1;
    }
    under = atoi(argv[3]);

    if (argc <= 4)
    {
        fprintf(stderr, "##### タイムスタンプ間隔を指定してください\n");
        return 1;
    }
    interval = atoi(argv[4]);

    buckets = (int *)malloc(under * sizeof(int));
    for (int i = 0; i < under; i++)
    {
        buckets[i] = 0;
    }

    time_start = gettime();
    bucket_sort(arr, n, buckets, under, interval, &time_log);
    time_stamp(&time_log, n);

    for (timelog *log = time_log; log != NULL; log = log->next)
        fprintf(stderr, "データ数: %d バケットソートの実行時間 = %lf[秒]\n", log->data_size, log->time_stamp - time_start);

    free(arr);
    free(buckets);
    free_time_log(time_log);

    return 0;
}