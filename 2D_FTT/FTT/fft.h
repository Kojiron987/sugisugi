/* ----------------------------------------------------------------------
   fft.h

   make_hamming
   revdmatrix1
   revdmatrix2
   make_sintbl
   make_bitrev
   fft

   Jan./31/'05 A.Sugimura
   ---------------------------------------------------------------------- */

void make_hamming(int n, double hamming[]);
void revdmatrix1(double **a, double **b, long nrl, long nrh, long ncl, long nch);
void revdmatrix2(double **a, double **b, long nrl, long nrh, long ncl, long nch);
int fft(int n, double x[], double y[]);

/* ---
static void make_sintbl(int n, double sintbl[]);
static void make_bitrev(int n, int bitrev[]);
   --- */
/* ---------------------------------------------------------------------- */
