#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MN 0
#define WIDTH 1
#define HEIGHT 2
#define LVALUE 3



int main(void) {
  FILE *fp;  /* ファイルポインタの宣言 */
  unsigned char s;
  unsigned char str;
  unsigned long data[256];
  int headdata[8];
  int flag = 0;
  int cntdata = 0;
  int n = 256;
  int tmp = 0;
  int max = 0;
  int mflag=0;
  int mode=2;
  int med0 =1;//med*2+1サイズ
  int med1 = 1;
  int med2 = 2;
  int med3 = 1;
  int med4 = 2;
  int med[5]={med0,med1,med2,med3,med4};
  float filt0[3][3] = {{1,1,1},{1,1,1},{1,1,1}};
  float filt1[3][3] = {{1,2,1},{2,4,2},{1,2,1}};
  float filt2[5][5] = {{-13,2,7,2,-13},{2,17,22,17,2},{7,22,27,22,7},{2,17,22,17,2},{-13,2,7,2,-13}};
  float filt3[3][3] =  {{1,1,1},{1,-8,1},{1,1,1}};
  float filt4[5][5] = {{4,1,0,1,4},{1,-2,-3,-2,1},{0,-3,4,-3,0},{1,-2,-3,-2,1},{4,1,0,1,4}};


  int modein=0;
  float filt[med[modein]*2+1][med[modein]*2+1];

  switch(modein){
  case 0:
    memcpy(filt,filt0, sizeof(filt0));
    break;
  case 1:
    memcpy(filt,filt1, sizeof(filt1));
    break;
  case 2:
    memcpy(filt,filt2, sizeof(filt2));
    break;
    case 3:
    memcpy(filt,filt3, sizeof(filt3));
    break;
  case 4:
    memcpy(filt,filt4, sizeof(filt4));
    break;
  }


  for(int q=0;q<med[modein]*2+1;q++){
    for(int q1=0;q1<med[modein]*2+1;q1++){
      printf("%12f",filt[q][q1]);
    }
    printf("\n");
  }

  memset(data,0,sizeof(data));
  if ((fp = fopen("../resources/town.pgm", "rb")) == NULL) {
    printf("file open error!!\n");
    return 1;
  }

  while(cntdata!=n){//n個のヘッダデータを読み込むまでループ
    str=fgetc(fp);

    if(str == 'P'){//先頭Pならヘッダ読込開始
      str=fgetc(fp);
      mode = str-'0';
      if(mode<0 || mode>6)
	exit(1);
    }
    if(str == '#'){
      while(str != '\n'){
	str=fgetc(fp);
      }
    }
    if(mode == 5){//P5なら3データ
      n = 4;
      if(isdigit(str)){
	tmp=tmp*10+(str-'0');
      }
      if(isspace(str)){
	headdata[cntdata]=tmp;
	cntdata++;
	tmp = 0;
      }
    }
  }

  //int asize = (med[mode]*2+1)*(med[mode]*2+1);
  unsigned char list[headdata[HEIGHT]][headdata[WIDTH]];
  unsigned char adata[headdata[HEIGHT]][headdata[WIDTH]];
  memset(list,0,sizeof(list));


  //printf("width=%d,height=%d,color=%d\n",headdata[3],headdata[1],headdata[2]);
  for(int i=0;i<headdata[HEIGHT];i++) {
    for(int j=0;j<headdata[WIDTH];j++){
      list[i][j]=fgetc(fp);
    }
  }
  fclose(fp);
  // memcpy(adata,list, sizeof(filt));


  for(int i=med[modein];i<headdata[HEIGHT]-med[modein];i++) {
    for(int j=med[modein];j<headdata[WIDTH]-med[modein];j++){
      float temp = 0;
      for(int i1=-1;i1<=1;i1++){
      	for(int j1=-1;j1<=1;j1++){
	          temp+=filt[i1+1][j1+1]*list[i+i1][j+j1];
	       }
      }

      switch(modein){
      case 0:
	adata[i][j]=(int)temp*1/9;
	break;
      case 1:
	adata[i][j]=(int)temp*1/16;
	break;
      case 2:
	adata[i][j]=(int)temp*1/175;
	break;
      case 3:
	adata[i][j]=(int)temp;
	break;
      case 4:
	adata[i][j]=(int)temp;
	break;
      }
    }
  }


  FILE *outputfile;
  outputfile = fopen("../resources/change.pgm", "w");
  if (outputfile == NULL) {
    printf("cannot open\n");
    exit(1);
  }
  fprintf(outputfile,"P%d\n",headdata[MN]);
  fprintf(outputfile,"%d\n",headdata[WIDTH]);
  fprintf(outputfile,"%d\n",headdata[HEIGHT]);
  fprintf(outputfile,"%d\n",headdata[LVALUE]);
  for(int i=0;i<headdata[HEIGHT];i++) {
    for(int j=0;j<headdata[WIDTH];j++){

      fprintf(outputfile,"%c",adata[i][j]);

    }
  }
  fclose(outputfile);
  return 0;
}
