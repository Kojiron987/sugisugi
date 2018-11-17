#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "median.h"

#define EDGEFILE "../resources/edgefile.pgm"
#define OUTPUTFILE "../resources/plot.txt"
#define COMMENT '#'
#define NEWLINE '\n'

enum PGMState{
  MAGIC = 0,
  WIDTH,
  HEIGHT,
  COLOR
};



struct pgm_t        // cotain pgm attribute
{
  char magic[5];
  int  width;
  int  height;
  int colorSize;
}pgm;

char token[5];    // 大きさは適当

FILE* fp;



void skipComment(void);
void getPgmToken(void);
void getToken(char c);
void cleanToken(void);
void printPgmToken(void);
void putEdgedPgm(int *Color);



int main(int argc, char* argv[])
{
  char c;
  int color;
  int *orgColor, *edgedColor;

  cleanToken();


  if((fp = fopen(argv[1], "rb")) == NULL)          // 読み取るファイルを引数から取り、開く
  {
    fprintf(stderr, "Failed to open file\n");
    exit(0);
  }

  getPgmToken();
  printPgmToken();    //デバグ用





  orgColor = malloc(sizeof(int) * pgm.width * pgm.height);
  edgedColor = malloc(sizeof(int) * pgm.width * pgm.height);




  for(int height = 0; height < pgm.height; height++)                  // 画素の読み取りを行う
    for(int width = 0; width < pgm.width; width++)
    {
        color = fgetc(fp);
        orgColor[height * pgm.width + width] = color;
        edgedColor[height * pgm.width + width] = color;
    }
  fclose(fp);


  /*
  printf("フィルタの選択\n 1: \n2: \n3: 4:\n");

  switch () {
    case:
  }

  */

  weighted_avarage(pgm.width, pgm.height, orgColor, edgedColor);
  weighted_avarage_ver2(pgm.width, pgm.height, orgColor, edgedColor);
  golay_filter(pgm.colorSize, pgm.width, pgm.height, orgColor, edgedColor);
  median_filter(pgm.width, pgm.height, orgColor, edgedColor);




  putEdgedPgm(edgedColor);

  free(orgColor);
  free(edgedColor);
  return 0;

}




















void skipComment()       //改行まで飛ばす
{
  char c;
  while((c = fgetc(fp)) != EOF && c != NEWLINE)
                    ;
  return;
}

void cleanToken(void) {     // tokenの中身をきれいにする
  int i;
  for(i = 0; i < 5; i++)
    token[i] = '\0';
}


void getPgmToken()         // pgm構造体に要素を格納
{
  char c;
  int flag = MAGIC;
  while((c = fgetc(fp)) != EOF)
  {
    if(c == COMMENT) {      // コメントは飛ばす
      skipComment();
    }
    else if(isspace(c)) {
      continue;
    }
    else {  // 空白文字でもコメントでもない場合、pgmファイルの要素が正しく
      switch (flag) {       // 入力ファイルにあるとして、要素を取り出す
      case MAGIC:           // magic word(P1, P2, P3, P4, P5, P6)の読み取り
        getToken(c);
        strcpy(pgm.magic, token);
        cleanToken();
        flag = WIDTH;
        break;
      case WIDTH:         // 画像の幅を読み取る
        getToken(c);
        pgm.width = atoi(token);
        cleanToken();
        flag = HEIGHT;
        break;
      case HEIGHT:        // 画像の高さを読み取る
        getToken(c);
        pgm.height = atoi(token);
        cleanToken();
        flag = COLOR;
        break;
      case COLOR:         // 画素の範囲を読み取る
        getToken(c);
        pgm.colorSize = atoi(token);
        cleanToken();
        return;        // color まで読んだら終了
      default:
        break;
      }
    }
  }
}
void getToken(char c)
{
  char thisC;
  int i = 0;
  token[i] = c;
  while((thisC = fgetc(fp)) != EOF && isspace(thisC) == 0)        //　区切り文字が現れるまで読み取る
  {
    i++;
    if(i >= 4 )                                                   // tokenに設定した文字より多かったときはエラーを出力する
    {
      perror("token's size over.");
      exit(0);
    }
    token[i] = thisC;
  }
  return;
}

void printPgmToken()            // デバグ用　pgmファイルの要素を出力する
{
  printf("magic word:%s width:%d height:%d colorSize:%d\n", pgm.magic, pgm.width, pgm.height, pgm.colorSize);
}


void putEdgedPgm(int *Color)
{
  FILE* wfp;
  wfp = fopen(EDGEFILE, "wb");

  if(wfp == NULL)
  {
    perror("could not open aa file");
    exit(1);
  }
  fprintf(wfp, "%s\n", pgm.magic);
  fprintf(wfp, "%d\n", pgm.width);
  fprintf(wfp, "%d\n", pgm.height);
  fprintf(wfp, "%d\n", pgm.colorSize);
  for(int height = 0; height < pgm.height; height++)                  // 画素の読み取りを行う
    for(int width = 0; width < pgm.width; width++)
    {
        fprintf(wfp, "%c", (char)Color[height * pgm.width + width]);
    }

    fclose(wfp);


}
