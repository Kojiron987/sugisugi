/* ----------------------------------------------------------------------
   2dfft.c

   $ cc -o 2dfft 2dfft.c fft2.c fft1.c -lm

   fft1.c の OPT に、1 または 0 を設定することで出力データの並びが変わる。

   Dec./20/'12 A.Sugimura
   Dec./20/'12 Last modified
   ---------------------------------------------------------------------- */

#include  <stdio.h>
#include  <stdlib.h>
#include  <math.h>
#include  "Params.h"

int fft2 (float a_rl[Y_SIZE][X_SIZE], float a_im[Y_SIZE][X_SIZE], int inv);

main()
{
  unsigned char  image[Y_SIZE][X_SIZE];
  float          ar[Y_SIZE][X_SIZE], ai[Y_SIZE][X_SIZE], d;
  int            x, y;
  char           buf[128];
  FILE           *fp;

  fprintf(stderr, "\n Program Start");

  fprintf(stderr, "\n pgm file read");

  fp = fopen("../sample/source.pgm", "rb");
  fgets(buf, 128, fp);  
  fgets(buf, 128, fp);  
  fgets(buf, 128, fp);  
  for(y = 0; y < Y_SIZE; y++)
    fread(&image[y][0], sizeof(char), X_SIZE, fp);
  fclose(fp);

  for(y = 0; y < Y_SIZE; y++)
    for(x = 0; x < X_SIZE; x++){
      ar[y][x] = (float)image[y][x];
      ai[y][x] = 0.0;
    }

  fprintf(stderr, "\n fft2");

  fft2((float (*)[X_SIZE])ar, (float (*)[X_SIZE])ai, 1);

  for(y = 0; y < Y_SIZE; y++){
    for(x = 0; x < X_SIZE; x++){
      d = ar[y][x]*ar[y][x]
        + ai[y][x]*ai[y][x];
      printf("%3d %3d %f\n", x, y, sqrt((double)d));
    }
    printf("\n");
  }

  fprintf(stderr, "\n Program End");
  fprintf(stderr, "\n\n");

}
