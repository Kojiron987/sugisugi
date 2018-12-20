/* ----------------------------------------------------------------------
   2dfft.c

   ２次元FFTプログラム

   $ cc -o 2dfft 2dfft.c fft.c memory.c -lm ( memory.h も必要 )

   Jan./10/'04 A.Sugimura
   ---------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "memory.h"

int main(int argc, char *argv[])
{  
  unsigned char **image, c;
  double **work1_re, **work1_im, **work2_re, **work2_im;
  double *Re, *Im, d;
  char  magic_number[2], buf[128];
  int   i, j, x, y, x_size, y_size;
  int   width, height, Maxval;
  int   flag;
  FILE  *fp;

  if(argc < 4){
    fprintf(stderr, "\n Usage: 2dfft in_file1 x_size y_size ");
    fprintf(stderr, "\n          in_file1 : input pgm file name");
    fprintf(stderr, "\n          x_size   : width(x)");
    fprintf(stderr, "\n          y_size   : height(y)");
    fprintf(stderr, "\n                    (x_size = y_size = 2^x)");
    fprintf(stderr, "\n\n");
    exit(1);
  }

  x_size = atoi(argv[2]);
  y_size = atoi(argv[3]);

/* ------------------------------
   memory allocation
   ------------------------------ */
  image = (unsigned char **)malloc_2D( x_size, y_size, sizeof **image);
  if(image == NULL){
    fprintf(stderr,"\n memory allocation error (image) ! \n\n");
    exit(1);
  }
  work1_re = (double **)dmatrix(0, y_size-1, 0, x_size-1);
  work1_im = (double **)dmatrix(0, y_size-1, 0, x_size-1);
  work2_re = (double **)dmatrix(0, y_size-1, 0, x_size-1);
  work2_im = (double **)dmatrix(0, y_size-1, 0, x_size-1);
  Re = (double *)malloc(sizeof *Re * x_size);
  if(Re == NULL){
    fprintf(stderr,"\n memory allocation error (Re)! \n\n");
    exit(1);
  }
  Im = (double *)malloc(sizeof *Re * x_size);
  if(Im == NULL){
    fprintf(stderr,"\n memory allocation error (Im)! \n\n");
    exit(1);
  }

/* ------------------------------
   pgm file open & read
   ------------------------------ */
  fp = fopen(argv[1], "rb");
  if(fp == NULL){
    fprintf(stderr, "\n file open error ( %s )\n\n", argv[1]);
    exit(1);
  }

  fgets(buf, 128, fp);
  if(!(buf[0]=='P' && buf[1]=='5')){
    fprintf(stderr, "\n not pgm file ( Magic number != P5 ) ( %s )\n\n",
                     argv[1]);
    fclose(fp);
    exit(1);
  }

  flag = 0;
  while(flag == 0){
    fgets(buf, 128, fp);
    if( buf[0] !='#')
      flag = 1;
  }
  sscanf(buf, "%d %d", &width, &height);
  if( width != x_size || height != y_size ){
    fprintf(stderr, "\n size error ( %s ) %d x %d != %d x %d \n\n",
                        argv[1], width, height, x_size, y_size);
    fclose(fp);
    exit(1);
  }

  flag = 0;
  while(flag == 0){
    fgets(buf, 128, fp);
    if( buf[0] !='#')
      flag = 1;
  }
  sscanf(buf, "%d", &Maxval);

  for( y=0; y<y_size; y++)
    fread(image[y], sizeof **image, (size_t)x_size, fp);

/* ------------------------------
   horizontal FFT
   ------------------------------ */
  for(j=0; j<y_size; j++){
    for(i=0; i<x_size; i++){
      Re[i]=(double)image[j][i];
      Im[i]=0;
    }
    fft(x_size, Re, Im);
    for(i=0; i<x_size; i++){
      work1_re[j][i]=Re[i];
      work1_im[j][i]=Im[i];
    }
  }

/* ------------------------------
   matrix reverse
   ------------------------------ */
  revdmatrix1(work1_re, work2_re, 0, y_size-1, 0, x_size-1);
  revdmatrix1(work1_im, work2_im, 0, y_size-1, 0, x_size-1);

/* ------------------------------
   virtical FFT
   ------------------------------ */
  for(j=0; j<y_size; j++){
    for(i=0; i<x_size; i++){
      Re[i]=work2_re[j][i];
      Im[i]=work2_im[j][i];
    }
    fft(x_size, Re, Im);
    for(i=0; i<x_size; i++){
      work1_re[j][i]=Re[i];
      work1_im[j][i]=Im[i];
    }
  }

/* ------------------------------
   matrix reverse
   ------------------------------ */
  revdmatrix2(work1_re, work2_re, 0, y_size-1, 0, x_size-1);
  revdmatrix2(work1_im, work2_im, 0, y_size-1, 0, x_size-1);

/* ------------------------------
   print data
   ------------------------------ */
  for(j=0; j<y_size; j++){
    for(i=0; i<x_size; i++){
      d = (work2_re[j][i] * work2_re[j][i])+(work2_im[j][i] * work2_im[j][i]);
      printf("%3d %3d %f\n", i, j, sqrt(d));
    }
    printf("\n");
  }

/* ------------------------------
   file close & memory free
   ------------------------------ */
  fclose(fp);
  free_2D( y_size, (char **)image);
  free_dmatrix(work1_re, 0, y_size-1, 0, x_size-1);
  free_dmatrix(work1_im, 0, y_size-1, 0, x_size-1);
  free_dmatrix(work2_re, 0, y_size-1, 0, x_size-1);
  free_dmatrix(work2_im, 0, y_size-1, 0, x_size-1);
  free(Re);
  free(Im);
}
