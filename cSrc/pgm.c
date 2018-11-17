#include "pgm.h"


void getPgmToken(const char* inFile, PGM_T *pgm)         // pgm構造体に要素を格納
{
  char c;
  int flag = MAGIC;

  if((pgmFp = fopen(inFile, "rb")) == NULL)          // 読み取るファイルを引数から取り、開く
  {
    fprintf(stderr, "Failed to open file\n");
    exit(0);
  }

  cleanToken();


  while((c = fgetc(pgmFp)) != EOF)
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
        strcpy(pgm->magic, token);
        cleanToken();
        flag = WIDTH;
        break;
      case WIDTH:         // 画像の幅を読み取る
        getToken(c);
        pgm->width = atoi(token);
        cleanToken();
        flag = HEIGHT;
        break;
      case HEIGHT:        // 画像の高さを読み取る
        getToken(c);
        pgm->height = atoi(token);
        cleanToken();
        flag = COLOR;
        break;
      case COLOR:         // 画素の範囲を読み取る
        getToken(c);
        pgm->colorSize = atoi(token);
        cleanToken();
        return;        // color まで読んだら終了
      default:
        break;
      }
    }
  }
}

void setPgmColor(int* orgColor, PGM_T* pgm)
{
  int color;
  // 画素情報を入手
  for(int height = 0; height < pgm->height; height++)                  // 画素の読み取りを行う
    for(int width = 0; width < pgm->width; width++)
    {
        color = fgetc(pgmFp);
        orgColor[height * pgm->width + width] = color;
    }
  fclose(pgmFp);
}

void skipComment()       //改行まで飛ばす
{
  int c;
  while((c = fgetc(pgmFp)) != EOF && c != NEWLINE)
                    ;
  return;
}

void cleanToken() {     // tokenの中身をきれいにする
  int i;
  for(i = 0; i < TOKEN_SIZE; i++)
    token[i] = '\0';
}

void getToken(char c)
{
  char thisC;
  int i = 0;
  token[i] = c;
  while((thisC = fgetc(pgmFp)) != EOF && isspace(thisC) == 0)        //　区切り文字が現れるまで読み取る
  {
    i++;
    if(i >= (TOKEN_SIZE - 1 ))                                                   // tokenに設定した文字より多かったときはエラーを出力する
    {
      perror("token's size over.");
      exit(0);
    }
    token[i] = thisC;
  }
  return;
}


void printPgmToken(PGM_T* pgm)            // デバグ用　pgmファイルの要素を出力する
{
  printf("magic word:%s width:%d height:%d colorSize:%d\n", pgm->magic, pgm->width, pgm->height, pgm->colorSize);
}



void putEdgedPgm(const char* outFile, int *Color, const PGM_T* pgm)
{
  FILE* wfp;
  wfp = fopen(outFile, "wb");

  if(wfp == NULL)
  {
    perror(":In putEdgedPgm function:  could not open the file");
    exit(1);
  }
  fprintf(wfp, "%s\n", pgm->magic);
  fprintf(wfp, "%d\n", pgm->width);
  fprintf(wfp, "%d\n", pgm->height);
  fprintf(wfp, "%d\n", pgm->colorSize);
  for(int height = 0; height < pgm->height; height++)                  // 画素の読み取りを行う
    for(int width = 0; width < pgm->width; width++)
    {
      fprintf(wfp, "%c", (char)Color[height * pgm->width + width]);
    }

  fclose(wfp);


}
