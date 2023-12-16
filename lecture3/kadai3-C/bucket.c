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

void bucket_sort(int arr[], int n, int buckets[], int under)
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
            arr[k] = i;
            k++;
        }
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

    if (argc <= 3)
    {
        fprintf(stderr, "##### 最大値を指定してください\n");
        return 1;
    }
    under = atoi(argv[3]);

    buckets = (int *)malloc(under * sizeof(int));
    for (int i = 0; i < under; i++)
    {
        buckets[i] = 0;
    }

    time_start = gettime();
    bucket_sort(arr, n, buckets, under);
    time_end = gettime();

    fprintf(stderr, "バッケトソートの実行時間 = %lf[秒]\n", time_end - time_start);

    for (int i = 0; i < n; i++)
        printf("%d\n", arr[i]);

    free(arr);
    free(buckets);

    return 0;
}