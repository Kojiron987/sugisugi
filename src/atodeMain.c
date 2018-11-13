#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "median.h"
#include "pgm.h"

#define OUTPUTFILE "../resources/plot.txt"




int main(int argc, char* argv[])
{
  PGM_T pgm;
  char c;
  int color;
  int *orgColor, *edgedColor;

  const char* outFile = "../resources/edgefile.pgm";

  getPgmToken(argv[1], &pgm, edgedColor);
  printPgmToken(&pgm);    //デバグ用

  edgedColor = malloc(sizeof(int) * pgm.width * pgm.height);
  orgColor = malloc(sizeof(int) * pgm.width * pgm.height);

  setPgmColor(orgColor, &pgm);  //今の所これを実行しなといgetPgmで開いたファイルポインタが閉じない fseek辺りを使う

  int point = 0;
  for(int height = 0; height < pgm.height; height++)
    for(int width = 0; width < pgm.width; width++) {
      point = height * pgm.width + width;
      edgedColor[point] = orgColor[point];
    }

  /*
  printf("フィルタの選択\n 1: \n2: \n3: 4:\n");

  switch () {
    case:
  }

  */

  weighted_avarage(pgm.width, pgm.height, orgColor, edgedColor);
//  weighted_avarage_ver2(pgm.width, pgm.height, orgColor, edgedColor);
//  golay_filter(pgm.colorSize, pgm.width, pgm.height, orgColor, edgedColor);
//  median_filter(pgm.width, pgm.height, orgColor, pgm.edgedColor);




  putEdgedPgm(outFile, edgedColor, &pgm);

  free(orgColor);
  free(edgedColor);
  return 0;

}
