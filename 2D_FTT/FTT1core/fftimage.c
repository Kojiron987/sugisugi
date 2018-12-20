#include  <stdio.h>
#include  <stdlib.h>
#include  <math.h>
#include  "Params.h"

int fft2 (float a_rl[Y_SIZE][X_SIZE], float a_im[Y_SIZE][X_SIZE], int inv);

/* --- fftimage --- 2次元 FFT の結果を画像化する ------------------------
          (X_SIZE, Y_SIZE が 2のべき乗の場合に限る)
    image_in:   入力画像配列
    image_out:  出力画像配列 (FFT)
   ---------------------------------------------------------------------- */
int fftimage(unsigned char image_in[Y_SIZE][X_SIZE],
             unsigned char image_out[Y_SIZE][X_SIZE])
{
    float    *ar;       /* データ実数部 (入出力兼用) */
    float    *ai;       /* データ虚数部 (入出力兼用) */
    double   norm, max;
    float    data;
    long     i, j;

    ar = (float *)malloc((size_t)Y_SIZE+X_SIZE*sizeof(float));
    ai = (float *)malloc((size_t)Y_SIZE+X_SIZE*sizeof(float));
    if ((ar == NULL) || (ai == NULL)) return -1;

    /* 原画像を読み込み、2次元 FFT の入力データに変換する */
    for (i = 0; i < Y_SIZE; i++) {
      for (j = 0; j < X_SIZE; j++) {
        ar[X_SIZE*i + j] = (float)image_in[i][j];
        ai[X_SIZE*i + j] = 0.0;
      }
    }

    /* 2次元 FFT を実行する */
    if (fft2((float (*))[X_SIZE])ar, (float (*))[X_SIZE])ai, 1) == -1) return -1;

    /* FFT の結果を画像化する */
    max = 0;
    for (i = 0; i < Y_SIZE; i++) {
      for (j = 0; j < X_SIZE; j++) {
        norm = ar[X_SIZE*i + j]*ar[X_SIZE+i + j]
             + ai[X_SIZE*i + j]*ai[X_SIZE+i + j];  /* 振幅成分計算 */
        if (norm != 0.0) norm = log(norm) / 2.0;
        else norm = 0.0;
        ar[X_SIZE*i + j] = (float)norm;
        if (norm > max) max = norm;
      }
    }
    for (i = 0; i < Y_SIZE; i++) {
      for (j = 0; j < X_SIZE; j++) {
        ar[X_SIZE*i + j] = (float)(ar[X_SIZE*i + j]*255 / max);
      }
    }

    /* FFT 結果を画像データに変換する */
    for (i = 0; i < Y_SIZE; i++) {
      for (j = 0; j < X_SIZE; j++) {
        data = ar[X_SIZE*i + j];
          if (data > 255) data = 255;
          if (data <   0) data =   0;
          image_out[i][j] = (unsigned char)data;
      }
    }    

    free(ar);
    free(ai);

    return 0;
}
