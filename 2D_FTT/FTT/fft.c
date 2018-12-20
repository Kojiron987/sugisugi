/* ----------------------------------------------------------------------
   fft.c

   void make_hamming(int n, double hamming[])
   int  fft(int n, double x[], double y[])

   static void make_sintbl(int n, double sintbl[])
   static void make_bitrev(int n, int bitrev[])

   May/27/'03 A.Sugimura
   ---------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* ------------------------------------------------------------ */
void make_hamming(int n, double hamming[])
{
    int i;

    for (i = 0; i < n; i++)
        hamming[i] = 0.546 - 0.454 * cos((2 * M_PI * i)/(n - 1));
}

/* ------------------------------------------------------------ */
void revdmatrix1(double **a, double **b, long nrl, long nrh, long ncl, long nch)
{
  long i, j, nrow=nrh-nrl+1, ncol=nch-ncl+1;

  for(j=0; j < nrow; j++){
    for(i=0; i < ncol; i++)
      b[i][j] = a[j][i];
  }
}

/* ------------------------------------------------------------ */
void revdmatrix2(double **a, double **b, long nrl, long nrh, long ncl, long nch)
{
  long i, j, nrow=nrh-nrl+1, ncol=nch-ncl+1;

  for(j=0; j < nrow; j++){
    for(i=0; i < ncol; i++)
      b[j][i] = a[i][j];
  }
}

/* ------------------------------------------------------------ */
static void make_sintbl(int n, double sintbl[])
{
    int i, n2, n4, n8;
    double c, s, dc, ds, t;

    n2 = n / 2;  n4 = n / 4;  n8 = n / 8;
    t = sin(M_PI / n);
    dc = 2 * t * t;  ds = sqrt(dc * ( 2 - dc));
    t = 2 * dc;  c = sintbl[n4] = 1;  s = sintbl[0] = 0;
    for (i = 1; i < n8; i++) {
        c -= dc;  dc += t * c;
        s += ds;  ds -= t * s;
        sintbl[i] = s;  sintbl[n4 - i] = c;
    }
    if (n8 != 0) sintbl[n8] = sqrt(0.5);
    for (i = 0; i < n4; i++)
        sintbl[n2 - i] = sintbl[i];
    for (i = 0; i < n2 + n4; i++)
        sintbl[i + n2] = - sintbl[i];
}

/* ------------------------------------------------------------ */
static void make_bitrev(int n, int bitrev[])
{
    int i, j, k, n2;

    n2 = n / 2;  i = j = 0;
    for ( ; ; ) {
        bitrev[i] = j;
        if (++i >= n) break;
        k = n2;
        while (k <= j) {  j -= k;  k /= 2;  }
        j += k;
    }
}

/* ------------------------------------------------------------ */
int fft(int n, double x[], double y[])
{
    static int      last_n = 0;                /* 前回呼出し時の n */
    static int     *bitrev = NULL;             /* ビット反転表     */
    static double  *sintbl = NULL;             /* 三角関数表       */
    int    i, j, k, ik, h, d, k2, n4, inverse;
    double t, s, c, dx, dy;

                                               /* 準備 */
    if (n < 0) {
        n = -n;  inverse = 1;                  /* 逆変換 */
    } else inverse = 0;
    n4 = n / 4;
    if (n != last_n || n == 0) {
        last_n = n;
        if (sintbl != NULL) free(sintbl);
        if (bitrev != NULL) free(bitrev);
        if (n == 0) return 0;                  /* 記憶領域を解放 */
        sintbl = malloc((n + n4) * sizeof(double));
        bitrev = malloc(n * sizeof(int));
        if (sintbl == NULL || bitrev == NULL) {
            fprintf(stderr, "memory error\n"); return 1;
        }
        make_sintbl(n, sintbl);
        make_bitrev(n, bitrev);
    }
    for (i = 0; i < n; i++) {                  /* ビット反転 */
        j = bitrev[i];
        if (i < j) {
            t = x[i];  x[i] = x[j];  x[j] = t;
            t = y[i];  y[i] = y[j];  y[j] = t;
        }
    }
    for (k = 1; k < n; k = k2) {               /* 変換 */
        h = 0;  k2 = k + k;  d = n / k2;
        for (j = 0; j < k; j++) {
            c = sintbl[h + n4];
            if (inverse) s = - sintbl[h];
            else         s =   sintbl[h];
            for (i = j; i < n; i += k2) {
                ik = i + k;
                dx = s * y[ik] + c * x[ik];
                dy = c * y[ik] - s * x[ik];
                x[ik] = x[i] - dx;  x[i] += dx;
                y[ik] = y[i] - dy;  y[i] += dy;
            }
            h += d;
        }
    }
    if (! inverse)                             /* 逆変換でないなら n で割る */
        for (i = 0; i < n; i++) {  x[i] /= n;  y[i] /= n;  }
    return 0;                                                /* 正常終了 */
}

/* ------------------------------------------------------------ */
