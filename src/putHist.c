#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>


#define OUTPUTFILE "../resources/plot.txt"
#define COMMENT '#'
#define NEWLINE '\n'
#define SPACE ' '
#define TAB '\t'

#define MAGIC 0
#define WIDTH 1
#define HEIGHT 2
#define COLOR 3


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
void printHist(const int*);

int main(int argc, char* argv[])
{
  char c;
  unsigned char uc;
  cleanToken();
  int color;

  if((fp = fopen(argv[1], "rb")) == NULL)          // 読み取るファイルを引数から取り、開く
  {
    fprintf(stderr, "Failed to open file\n");
    exit(0);
  }

  getPgmToken();
  printPgmToken();    //デバグ用

  int colorHist[pgm.colorSize + 1];                     // 色素の大きさだけ配列を確保する 0 ~ colorSize
  for(int i = 0; i <= pgm.colorSize; i++)            // 配列を初期化する
    colorHist[i] = 0;

//  while((c = fgetc(fp)) != EOF && c != NEWLINE)    // 画素のところまで空白等をとばす
//                    ;

  for(int width = 0; width < pgm.width; width++)                  // 画素の読み取りを行う
    for(int height = 0; height < pgm.height; height++)
    {
        color =  fgetc(fp);
        colorHist[color]++;
    }

  int cnt = 0;
  for(int i = 0; i <= pgm.colorSize; i++)            // ヒストグラムの出力
  {
    printf("(%d, %d)\n", i, colorHist[i]);
    cnt += colorHist[i];
  }

  //------------------------------------------------- dubug

  if(cnt == (pgm.width * pgm.height))
    printf("ok\n");
  printf("cnt:%d size:%d\n", cnt, pgm.width * pgm.height);
  //-------------------------------------------------
  fclose(fp);

  printHist(colorHist);      // ファイルに結果を書き込む

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
    switch (c) {             // コメントは飛ばす
    case COMMENT:
      skipComment();
      break;

    case NEWLINE:           // 空白等は飛ばす
    case TAB:
    case SPACE:
      break;

    default:                // 空白文字でもコメントでもない場合、pgmファイルの要素が正しく
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
      break;
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

void printHist(const int* temp)                  // 結果を書き込む関数
{
  FILE* wfp;        // 書き込み用のファイルポインタ

  wfp = fopen(OUTPUTFILE, "w");
  if(wfp == NULL)
  {
    perror("could not open file");
    exit(1);
  }

  for(int i = 0; i <= pgm.colorSize; i++)
  {
    fprintf(wfp, "%d\n", temp[i]);
  }

  fclose(wfp);



}
