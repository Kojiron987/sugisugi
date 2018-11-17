#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/* PGMファイルの要素の読み取りを行う  */

#define COMMENT '#'
#define TOKEN_SIZE 5
#define NEWLINE '\n'

enum PGMState{
  MAGIC = 0,
  WIDTH,
  HEIGHT,
  COLOR
};

typedef struct pgm_t        // cotain pgm attribute
{
  char magic[5];
  int  width;
  int  height;
  int colorSize;
}PGM_T;


FILE* pgmFp;        // getPgmTokenに引数としてpgmファイルを渡す
char token[TOKEN_SIZE];    // 大きさは適当



void getPgmToken(const char* inFile, PGM_T* pgm);
void skipComment(void);
void getToken(char c);
void cleanToken(void);
void printPgmToken(PGM_T* pgm);
void putEdgedPgm(const char* outFile, int *Color, const PGM_T* pgm);
void setPgmColor(int * orgColor, PGM_T* pgm);
