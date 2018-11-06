#include "median.h"
#include <stdio.h>



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



void weighted_avarage(int width, int height, int orgColor[][height], int color[][height])
{

  /*int count = 0;
  for(int i = 0; i < 5 ;i++)
    for(int j= 0; j < 5; j++)
      count += Golay[i][j];
  printf("aaa = %d\n", count);*/
  for(int i = 1; i < (width - 1); i++)
    for(int j = 1; j < (height -1); j++)     // ←お前だ！！(ノイズの原因)
    {
      color[i][j] = (int)((
        orgColor[i-1][j-1] * test[0][0] + orgColor[i-1][j] * test[1][0] + orgColor[i-1][j+1] * test[2][0]
      + orgColor[i][j-1]   * test[0][1] + orgColor[i][j]   * test[1][1] + orgColor[i][j+1]   * test[2][1]
      + orgColor[i+1][j-1] * test[0][2] + orgColor[i+1][j] * test[1][2] + orgColor[i+1][j+1] * test[2][2]) / 1);

      /*
      color[i][j] =(int)
      ((orgColor[i-1][j-1] + orgColor[i][j-1] + orgColor[i+1][j-1]
      + orgColor[i-1][j]   + orgColor[i][j]   + orgColor[i+1][j]
      + orgColor[i-1][j+1] + orgColor[i][j+1] + orgColor[i+1][j+1]) / 9);
      */
      //printf("%d\n", j);
    }
}
