#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define N 50

// 隣接行列用のデータ構造の定義
#define boolean int              // C 言語には boolean 型がないので，ここで (無理矢理) 宣言
#define true 1                   // C 言語で真偽値を扱う場合，0 が偽，非 0 が真となるが，
#define false 0                  // テキストに合わせて true, false を定義しておく
typedef boolean adjmatrix[N][N]; // テキストでは変数定義になっているが，ここでは型として宣言

typedef int vindex;

typedef struct edgecell
{
    vindex destination;
    struct edgecell *next;
} edgecell;

typedef edgecell *vertices[N];

typedef struct
{
    int vertex_num;
    int edge_num;
    vertices vtop;
} graph;

int read_adjacency_matrix(char *datafile, adjmatrix mat)
{
    FILE *fp;
    int vertex_num;
    vindex src, dest;

    fp = fopen(datafile, "r");
    fscanf(fp, "%d\n", &vertex_num);
    if (vertex_num >= N)
    {
        fprintf(stderr, "#### このプログラムが扱えるのは頂点数が%d までです\n", N);
        exit(1);
    }
    for (src = 0; src < vertex_num; src++)
    {
        for (dest = 0; dest < vertex_num; dest++)
        {
            fscanf(fp, "%d\n", &mat[src][dest]); // 隣接行列の要素を１つずつ読み込む
        }
    }
    fclose(fp); // ファイルを閉
    return vertex_num;
}

void add_edge(graph *g, vindex src, vindex dest)
{
    edgecell *edge = (edgecell *)malloc(sizeof(edgecell));
    edge->destination = dest;
    edge->next = g->vtop[src];
    g->vtop[src] = edge;
}

// 隣接行列からグラフを作成 (テキスト指定のデータ構造)
void translate_into_graph(adjmatrix mat, graph *g)
{
    vindex src, dest;
    for (src = 0; src < g->vertex_num; src++)
    {
        for (dest = 0; dest < g->vertex_num; dest++)
        {
            if (mat[src][dest])
            {
                add_edge(g, src, dest);
            }
        }
    }
}

void print_graph(graph *g)
{
    vindex v;
    printf("digraph G {\n");
    printf("  size=\"11.5,8\"; node[fontsize=10,height=0.01,width=0.01]; edge[len=3.0];\n");
    for (v = 0; v < g->vertex_num; v++)
    {
        edgecell *edge;
        for (edge = g->vtop[v]; edge != NULL; edge = edge->next)
        {
            printf("  %d -> %d;\n", v + 1, edge->destination + 1);
        }
    }
    printf("}\n");
}

void free_graph(graph *g)
{
    vindex v;
    for (v = 0; v < g->vertex_num; v++)
    {
        edgecell *edge, *next_edge;
        for (edge = g->vtop[v]; edge != NULL; edge = next_edge)
        {
            next_edge = edge->next;
            free(edge);
        }
    }
}

void init_matrix(adjmatrix *mat, int s)
{
    int i, j;
    for (i = 0; i < s; i++)
    {
        for (j = 0; j < s; j++)
        {
            (*mat)[i][j] = 0;
        }
    }
}

void copy_matrix(adjmatrix mat, adjmatrix *copy, int s)
{
    int i, j;
    for (i = 0; i < s; i++)
    {
        for (j = 0; j < s; j++)
        {
            (*copy)[i][j] = mat[i][j];
        }
    }
}

void multiply_matrix(adjmatrix a, adjmatrix b, adjmatrix *ans, int s)
{
    int i, j, k;
    for (i = 0; i < s; i++)
    {
        for (j = 0; j < s; j++)
        {
            for (k = 0; k < s; k++)
            {
                (*ans)[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void print_matrix(adjmatrix mat, int s)
{
    vindex i, j;
    for (i = 0; i < s; i++)
    {
        for (j = 0; j < s; j++)
        {
            printf("%d", mat[i][j]);
            if (mat[i][j] < 10)
                printf(" ");
            if (mat[i][j] < 100)
                printf(" ");
        }
        puts("");
    }
}

void power_matrix(adjmatrix mat, adjmatrix *ans, int s, int n)
{
    int v;
    adjmatrix temp;
    copy_matrix(mat, &temp, s);
    for (v = 0; v < n - 1; v++)
    {
        init_matrix(ans, s);
        multiply_matrix(mat, temp, ans, s);
        copy_matrix(*ans, &temp, s);
    }
}

int find_path(graph *g, int i, int j)
{
    vindex v;
    for (v = 0; v < g->vertex_num; v++)
    {
        edgecell *edge;
        for (edge = g->vtop[v]; edge != NULL; edge = edge->next)
        {
            printf("  %d -> %d;\n", v + 1, edge->destination + 1);
        }
    }
    return 1;
}

int main(int argc, char *argv[])
{
    char *datafile; // 入力データのファイル名
    adjmatrix mat;
    adjmatrix ans;
    graph g;

    if (argc <= 1)
    {
        fprintf(stderr, "##### ファイル名を指定してください\n");
        return 1;
    }
    datafile = argv[1]; // ファイル名の取得
    g.vertex_num = read_adjacency_matrix(datafile, mat);
    power_matrix(mat, &ans, g.vertex_num, g.vertex_num - 1);
    print_matrix(ans, g.vertex_num);
    // translate_into_graph(mat, &g);
    // print_graph(&g);
    // free_graph(&g);
    return 0;
}