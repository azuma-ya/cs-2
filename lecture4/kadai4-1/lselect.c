#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <sys/time.h>

#define SMALL_N 50

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

void select_sort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        swap(&arr[min_idx], &arr[i]);
    }
}

int l_select(int arr[], int n, int k)
{
    if (n < SMALL_N)
    {
        select_sort(arr, n);
        return arr[k - 1];
    }

    // 5個の要素からなるグループに分割してソート
    for (int i = 0; i < n / 5; i++)
    {
        select_sort(arr + i * 5, 5);
    }

    // 中央値の中央値（m）を求める
    int *medians = (int *)malloc((n / 5) * sizeof(int));
    for (int i = 0; i < n / 5; i++)
    {
        medians[i] = arr[i * 5 + 2]; // グループ内の中央の要素を取得
    }

    int m = l_select(medians, n / 5, n / 10);

    free(medians);

    // 中央値を基準にして3つの部分集合に分割
    int *S1 = NULL, *S2 = NULL, *S3 = NULL;
    int size_S1 = 0, size_S2 = 0, size_S3 = 0;

    for (int i = 0; i < n; i++)
    {
        if (arr[i] < m)
        {
            size_S1++;
            S1 = (int *)realloc(S1, size_S1 * sizeof(int));
            S1[size_S1 - 1] = arr[i];
        }
        else if (arr[i] == m)
        {
            size_S2++;
            S2 = (int *)realloc(S2, size_S2 * sizeof(int));
            S2[size_S2 - 1] = arr[i];
        }
        else
        {
            size_S3++;
            S3 = (int *)realloc(S3, size_S3 * sizeof(int));
            S3[size_S3 - 1] = arr[i];
        }
    }

    // 条件に基づいて再帰的に l-select を呼び出す
    if (k <= size_S1)
    {
        int answer = l_select(S1, size_S1, k);
        free(S1);
        free(S2);
        free(S3);
        return answer;
    }
    else if (k <= size_S1 + size_S2)
    {
        free(S1);
        free(S2);
        free(S3);
        return m;
    }
    else
    {
        int answer = l_select(S3, size_S3, k - size_S1 - size_S2);
        free(S1);
        free(S2);
        free(S3);
        return answer;
    }
}

int main(int argc, char *argv[])
{
    char *datafile; // 入力データのファイル名
    FILE *fp;       // 入力データのファイルポインタ
    int n;          // 入力データのデータ数
    int *arr;       // 入力データ格納場所
    double time_start, time_end;
    int answer;
    int k;

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

    if (argc <= 3)
    {
        fprintf(stderr, "##### k番目を指定してください\n");
        return 1;
    }
    k = atoi(argv[3]);

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
    answer = l_select(arr, n, k);
    time_end = gettime();

    printf("答え = %d\n", answer);

    fprintf(stderr, "k番目選択の実行時間 = %lf\n", time_end - time_start);

    free(arr);

    return 0;
}