#include  <stdio.h>
#include  <stdlib.h>
#include  <math.h>

#define PI   3.141592
#define OPT  1        /* OPT = 1 光学的 DFT (直流分が中央) */
                      /* OPT = 0 通常の DFT (直流分が左端) */

void fft1core(float a_rl[], float a_im[], int length,
             int ex, float sin_tbl[], float cos_tbl[], float buf[]);

void cstb(int length, int inv, float sin_tbl[], float cos_tbl[]);

void birv(float a[], int length, int ex, float b[]);

/* --- fft1 --- 1次元 FFT の実行 ----------------------------------------
    a_rl:  データ実数部 (入出力兼用)
    a_im:  データ虚数部 (入出力兼用)
    ex:    データ個数を 2のべき乗で与える (データ個数 = 2のex乗個)
    inv:   1: DFT, -1: 逆 DFT
   ---------------------------------------------------------------------- */
int fft1(float a_rl[], float a_im[], int ex, int inv)
{
    int    i, length = 1;
    float  *sin_tbl;      /* sin計算用テーブル */
    float  *cos_tbl;      /* cos計算用テーブル */
    float  *buf;          /* 作業用バッファ    */

    for (i = 0; i < ex; i++) length *= 2;  /* データ個数の計算 */
    sin_tbl = (float *)malloc((size_t)length*sizeof(float));
    cos_tbl = (float *)malloc((size_t)length*sizeof(float));
    buf = (float *)malloc((size_t)length*sizeof(float));
    if ((sin_tbl == NULL) || (cos_tbl == NULL) || (buf == NULL)) {
      return -1;
    }
    cstb(length, inv, sin_tbl, cos_tbl);  /* sin, cos テーブル作成 */
    fft1core(a_rl, a_im, length, ex, sin_tbl, cos_tbl, buf);

    free(sin_tbl);
    free(cos_tbl);

    return 0;
}

/* --- fft1core --- 1次元 FFT の計算ん核になる部分 ----------------------
    a_rl:     データ実数部 (入出力兼用)
    a_im:     データ虚数部 (入出力兼用)
    ex:       データ個数を 2のべき乗で与える (データ個数 = 2のex乗個)
    sin_tbl:  sin計算用テーブル
    cos_tbl:  cos計算用テーブル
   ---------------------------------------------------------------------- */
void fft1core(float a_rl[], float a_im[], int length,
              int ex, float sin_tbl[], float cos_tbl[], float buf[])
{
    int   i, j, k, w, j1, j2;
    int   numb, lenb, timb;
    float xr, xi, yr, yi, nrml;

    if (OPT == 1){
      for (i = 1; i < length; i+=2) {
        a_rl[i] = -a_rl[i];
        a_im[i] = -a_im[i];
      }
    }
    numb = 1;
    lenb = length;
    for (i = 0; i < ex; i++) {
      lenb /= 2;
      timb = 0;
      for (j = 0; j < numb; j++) {
        w = 0;
        for (k = 0; k < lenb; k++) {
          j1 = timb + k;
          j2 = j1 + lenb;
          xr = a_rl[j1];
          xi = a_im[j1];
          yr = a_rl[j2];
          yi = a_im[j2];
          a_rl[j1] = xr + yr;
          a_im[j1] = xi + yi;
          xr = xr - yr;
          xi = xi - yi;
          a_rl[j2] = xr*cos_tbl[w] - xi*sin_tbl[w];
          a_im[j2] = xr*sin_tbl[w] + xi*cos_tbl[w];
          w += numb;
        }
        timb += (2*lenb);
      }
      numb *= 2;
    }
    birv(a_rl, length, ex, buf);  /* 実数データの並べ換え */
    birv(a_im, length, ex, buf);  /* 虚数データの並べ換え */
    if (OPT == 1) {
      for (i = 1; i < length; i+=2) {
        a_rl[i] = -a_rl[i];
        a_im[i] = -a_im[i];
      }
    }
    nrml = (float)(1.0 / sqrt((float)length));
    for (i = 0; i < length; i++) {
      a_rl[i] *= nrml;
      a_im[i] *= nrml;
    }
}


/* --- cstb --- sin, cos テーブル作成 -----------------------------------
    length:   データ個数
    inv:      1: DFT, -1: 逆 DFT
    sin_tbl:  sin計算用テーブル
    cos_tbl:  cos計算用テーブル
   ---------------------------------------------------------------------- */
void cstb(int length, int inv, float sin_tbl[], float cos_tbl[])
{
    int    i;
    float  xx, arg;

    xx = (float)(((-PI) * 2.0) / (float)length);
    if (inv < 0) xx = -xx;
    for (i = 0; i < length; i++) {
      arg = (float)i * xx;
      sin_tbl[i] = (float)sin(arg);
      cos_tbl[i] = (float)cos(arg);
    }
}


/* --- birv --- データの並べ換え ----------------------------------------
    a:       データの配列
    length:  データ個数
    ex:      データ個数をを 2のべき乗で与える (データ個数 = 2のex乗個)
    b:       作業用ブッファ
   ---------------------------------------------------------------------- */
void birv(float a[], int length, int ex, float b[])
{
    int  i, ii, k, bit;

    for (i = 0; i < length; i++) {
      for (k = 0, ii=i, bit=0; ; bit<<=1, ii>>=1) {
        bit = (ii & 1) | bit;
        if (++k == ex) break;
      }
      b[i] = a[bit];
    }
    for (i = 0; i < length; i++)
      a[i] = b[i];
}
