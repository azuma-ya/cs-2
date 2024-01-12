#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <sys/time.h>

int debug = 1;

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

void shaker_sort(int array[], int n)
{
    int swapped;
    int start = 0;
    int end = n - 1;

    do
    {
        // 前方方向のパス
        swapped = 0;
        for (int i = start; i < end; ++i)
        {
            if (array[i] > array[i + 1])
            {
                // 隣接する要素を比較して、必要なら交換
                int temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;
                swapped = 1;
            }
        }

        // 後方方向のパス
        if (!swapped)
        {
            // 前方方向のパスで交換が行われなかったら終了
            break;
        }

        swapped = 0;
        --end;

        for (int i = end - 1; i >= start; --i)
        {
            if (array[i] > array[i + 1])
            {
                // 隣接する要素を比較して、必要なら交換
                int temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;
                swapped = 1;
            }
        }

        ++start;
        if (debug)
        {
            for (int j = 0; j < n; j++)
                printf("%d ", array[j]);
            printf("\n");
        }
    } while (swapped);
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
    if (debug)
    {
        for (int j = 0; j < n; j++)
            printf("%d ", arr[j]);
        printf("\n");
    }
    shaker_sort(arr, n);
    time_end = gettime();

    for (int i = 0; i < n; i++)
        printf("%d\n", arr[i]);

    fprintf(stderr, "データ数: %d シェイカーの実行時間 = %lf[秒]\n", n, time_end - time_start);

    free(arr);

    return 0;
}