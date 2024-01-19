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

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int left[n1], right[n2];

    for (i = 0; i < n1; i++)
        left[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        right[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (left[i] <= right[j])
        {
            arr[k] = left[i];
            i++;
        }
        else
        {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = left[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = right[j];
        j++;
        k++;
    }
}

void merge_sort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

int selectk(int arr[], int n, int k)
{
    int answer;

    if (n < SMALL_N)
    {
        merge_sort(arr, 0, n - 1);
        return arr[k - 1];
    }

    int p = arr[random() % n];
    int u = 0;
    int v = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] < p)
            u++;
        if (arr[i] <= p)
            v++;
    }
    if (k <= u)
    {
        int *U = (int *)malloc(u * sizeof(int));
        int used = 0;
        for (int i = 0; i < n; i++)
        {
            if (arr[i] < p)
                U[used++] = arr[i];
        }
        answer = selectk(U, u, k);
        free(U);
        return answer;
    }
    if (k <= v)
        return p;
    int *V = (int *)malloc((n - v) * sizeof(int));
    int used = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > p)
            V[used++] = arr[i];
    }
    answer = selectk(V, n - v, k - v);
    free(V);
    return answer;
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
    answer = selectk(arr, n, k);
    time_end = gettime();

    printf("答え = %d\n", answer);

    fprintf(stderr, "k番目選択の実行時間 = %lf\n", time_end - time_start);

    free(arr);

    return 0;
}