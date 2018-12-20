#include  <stdio.h>
#include  <stdlib.h>
#include  <math.h>
#include  "Params.h"

void fft1core(float a_rl[], float a_im[], int length,
              int ex, float sin_tbl[], float cos_tbl[], float buf[]);

void cstb(int length, int inv, float sin_tbl[], float cos_tbl[]);

void rvmtx1(float a[Y_SIZE][X_SIZE], float b[X_SIZE][Y_SIZE],
            int xsize, int ysize);

void rvmtx2(float a[X_SIZE][Y_SIZE], float b[Y_SIZE][X_SIZE],
            int xsize, int ysize);

/* --- fft2 --- 2次元FFTの実行 ----------------------------------------
          (X_SIZE, Y_SIZEが2のべき乗の場合に限る)
    a_rl: データ実数部(入出力兼用)
    a_im: データ虚数部(入出力兼用)
    inv:  1: DFT, -1: 逆DFT
   --- fft2 --- 2次元FFTの実行 ---------------------------------------- */
int fft2(float a_rl[Y_SIZE][X_SIZE], float a_im[Y_SIZE][X_SIZE], int inv)
{
    float   *b_rl;     /* データ転置作業用配列 (実数部) */
    float   *b_im;     /* データ転置作業用配列 (虚数部) */
    float   *hsin_tbl; /* 水平用sin計算用テーブル       */
    float   *hcos_tbl; /* 水平用cos計算用テーブル       */
    float   *vsin_tbl; /* 垂直用sin計算用テーブル       */
    float   *vcos_tbl; /* 垂直用cos計算用テーブル       */
    float   *buf_x;    /* 作業用バッファ (水平方向)     */
    float   *buf_y;    /* 作業用バッファ (垂直方向)     */
    int     i;

    b_rl = (float *)calloc((size_t)X_SIZE*Y_SIZE, sizeof(float));
    b_im = (float *)calloc((size_t)X_SIZE*Y_SIZE, sizeof(float));
    hsin_tbl = (float *)calloc((size_t)X_SIZE, sizeof(float));
    hcos_tbl = (float *)calloc((size_t)X_SIZE, sizeof(float));
    vsin_tbl = (float *)calloc((size_t)X_SIZE, sizeof(float));
    vcos_tbl = (float *)calloc((size_t)X_SIZE, sizeof(float));
    buf_x = (float *)malloc((size_t)X_SIZE*sizeof(float));
    buf_y = (float *)malloc((size_t)Y_SIZE*sizeof(float));
    if ((b_rl == NULL) || (b_im == NULL)
        || (hsin_tbl == NULL) || (hcos_tbl == NULL)
        || (vsin_tbl == NULL) || (vcos_tbl == NULL)
        || (buf_x == NULL) || (buf_y == NULL)) {
      return -1;
    }

    cstb(X_SIZE, inv, hsin_tbl, hcos_tbl);  /* 水平用sin,cosテーブル作成 */
    cstb(Y_SIZE, inv, vsin_tbl, vcos_tbl);  /* 垂直用sin,cosテーブル作成 */

    /* 水平方向の FFT */
    for (i = 0; i < Y_SIZE; i++) {
      fft1core(&a_rl[(long)i][0], &a_im[(long)i][0],
               X_SIZE, X_EXP, hsin_tbl, hcos_tbl, buf_x);
    }

    /* 2次元データの配置 */
    rvmtx1((float (*)[X_SIZE])a_rl, (float (*)[X_SIZE])b_rl, X_SIZE, Y_SIZE);
    rvmtx1((float (*)[X_SIZE])a_im, (float (*)[X_SIZE])b_im, X_SIZE, Y_SIZE);

    /* 垂直方向の FFT */
    for (i = 0; i < X_SIZE; i++) {
      fft1core(&b_rl[(long)Y_SIZE*i], &b_im[(long)Y_SIZE*i],
               Y_SIZE, Y_EXP, vsin_tbl, vcos_tbl, buf_y);
    }

    /* 2次元データの配置 */
    rvmtx2((float (*)[Y_SIZE])b_rl, (float (*)[Y_SIZE])a_rl, X_SIZE, Y_SIZE);
    rvmtx2((float (*)[Y_SIZE])b_im, (float (*)[Y_SIZE])a_im, X_SIZE, Y_SIZE);

    free(b_rl);
    free(b_im);
    free(hsin_tbl);
    free(vsin_tbl);
    free(hcos_tbl);
    free(vcos_tbl);

    return 0;
}

/* --- rvmtx1 --- 2次元データの転置 -----------------------------------
     a: 2次元入力データ
     b: 2次元出力データ
     xsize: 水平データ個数
     ysize: 垂直データ個数
   -------------------------------------------------------------------- */
void rvmtx1(float a[Y_SIZE][X_SIZE], float b[X_SIZE][Y_SIZE],
            int xsize, int ysize)
{
    int  i, j;

    for (i = 0; i < ysize; i++) {
      for (j = 0; j < xsize; j++)
        b[j][i] = a[i][j];
    }

}
 
/* --- rvmtx2 --- 2次元データの転置 -----------------------------------
     a: 2次元入力データ
     b: 2次元出力データ
     xsize: 水平データ個数
     ysize: 垂直データ個数
   -------------------------------------------------------------------- */
void rvmtx2(float a[Y_SIZE][X_SIZE], float b[X_SIZE][Y_SIZE],
            int xsize, int ysize)
{
    int  i, j;

    for (i = 0; i < ysize; i++) {
      for (j = 0; j < xsize; j++)
        b[i][j] = a[j][i];
    }

}
 
