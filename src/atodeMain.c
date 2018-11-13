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
  int filter_flag;
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

  // 使うフィルタの選択

  printf("フィルタの選択\n1: 平滑フィルタ9\n2: 平滑フィルタ16\n3: Golayフィルタ\n4: 平均化フィルタ\n> ");
  scanf("%d", &filter_flag);
  switch (filter_flag) {
  case 1:
    weighted_avarage(pgm.width, pgm.height, orgColor, edgedColor);
    break;
  case 2:
    weighted_avarage_ver2(pgm.width, pgm.height, orgColor, edgedColor);
    break;
  case 3:
    golay_filter(pgm.colorSize, pgm.width, pgm.height, orgColor, edgedColor);
    break;
  case 4:
     median_filter(pgm.width, pgm.height, orgColor, edgedColor);
    break;
  default:
    printf("不正な入力です\n");
    exit(1);
    break;
  }

  // フィルタを通した画像データの出力
  putEdgedPgm(outFile, edgedColor, &pgm);

  // メモリの開放
  free(orgColor);
  free(edgedColor);
  return 0;

}
