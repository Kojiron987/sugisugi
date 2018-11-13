#include "median.h"



double nine[][3] = {
  {1.0 / 9.0,1.0/ 9.0 ,1.0 / 9.0},
  {1.0 / 9.0,1.0/ 9.0 ,1.0 / 9.0},
  {1.0 / 9.0,1.0/ 9.0 ,1.0 / 9.0}
};

double sixteen [][3] = {
  {1, 2, 1},
  {2, 4, 2},
  {1, 2, 1}
};

int Golay[][5] = {
  {-13, 2, 7, 2, -13},
  {2, 17, 22, 17, 2},
  {7, 22, 27, 22, 7},
  {2, 17, 22, 17, 2},
  {-13, 2, 7, 2, -13}
};


int test[][3] = {
  {0, 0, 0},
  {0, 1, 0},
  {0, 0, 0}
};




void weighted_avarage(int width, int height, const int *orgColor, int *edgedColor)
{
  for(int i = 1; i < (width - 1); i++)
    for(int j = 1; j < (height -1); j++)
      for(int i1=-1;i1<=1;i1++){
        for(int j1=-1;j1<=1;j1++){
            edgedColor[i * height + j] = nine[i1+1][j1+1]*orgColor[(i+i1) * height + (j+j1)];
          }
        }
}

void weighted_avarage_ver2(int width, int height, const int *orgColor, int *edgedColor)
{
  for(int i = 1; i < (width - 1); i++)
    for(int j = 1; j < (height -1); j++)
      for(int i1=-1;i1<=1;i1++){
        for(int j1=-1;j1<=1;j1++){
            edgedColor[i * height + j] = sixteen[i1+1][j1+1]*orgColor[(i+i1) * height + (j+j1)];
          }
        }
}


void golay_filter(int colorSize, int width, int height, const int *orgColor, int *edgedColor)
{
  int tmp = 0;
  for(int i = 2; i < (width - 2); i++)
    for(int j = 2; j < (height - 2); j++)
      for(int i1=-1;i1<=1;i1++){
        for(int j1=-1;j1<=1;j1++){
            tmp = Golay[i1+1][j1+1]*orgColor[(i+i1) * height + (j+j1)];
            if(tmp < 0)
              edgedColor[i * height + j] = 0;
            else if(tmp > colorSize)
              edgedColor[i * height + j] = 255;
            else
              edgedColor[i * height + j] = tmp;
          }
        }
}
