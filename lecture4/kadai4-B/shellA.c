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

void shell_sort(int arr[], int n)
{
    int h[] = {9, 5, 3, 1};

    for (int m = 0; m < 4; m++)
    {
        int k = h[m];

        for (int i = k; i < n; i++)
        {
            int x = arr[i];
            int j = i - k;

            while (j >= 0 && x < arr[j])
            {
                arr[j + k] = arr[j];
                j -= k;
            }
            arr[j + k] = x;
        }
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
    shell_sort(arr, n);
    time_end = gettime();

    for (int i = 0; i < n; i++)
        printf("%d\n", arr[i]);

    fprintf(stderr, "データ数: %d シェルソートの実行時間 = %lf[秒]\n", n, time_end - time_start);

    free(arr);

    return 0;
}