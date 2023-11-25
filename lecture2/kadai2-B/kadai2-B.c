#include <stdio.h>

#define N 5

// 隣接行列用のデータ構造の定義
#define boolean int // C 言語には boolean 型がないので，ここで (無理矢理) 宣言
#define true 1 // C 言語で真偽値を扱う場合，0 が偽，非 0 が真となるが，
#define false 0 // テキストに合わせて true, false を定義しておく
typedef boolean adjmatrix[N][N]; // テキストでは変数定義になっているが，ここでは型として宣言

// 隣接行列からグラフを作成 (テキスト指定のデータ構造)
void translate_into_graph( adjmatrix mat, graph *g ) {
// この関数を完成させよ
// 隣接行列の要素が 1 なら有向辺があるということ → 有向辺を追加 (関数 add edge を使う)
}

int main(int argc, char *argv[]){
  char *datafile; // 入力データのファイル名
  if ( argc <=1) {
    fprintf(stderr, "##### ファイル名を指定してください\n" );
    return 1;
  }
  datafile = argv[1]; // ファイル名の取得
  translate_into_graph();
}