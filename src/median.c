#include "median.h"




int nine[][3] = {
  {1,1,1},
  {1,1,1},
  {1,1,1}
};

int sixteen [][3] = {
  {1, 2, 1},
  {2, 4, 2},
  {1, 2, 1}
};

int Golay[][5] = {
  {-13, 2, 7, 2, -13},
  {2, 17, 22, 17, 2},
  {7, 22, 27, 22, 7},
  {7, 17, 27, 17, 2},
  {-13, 2, 7, 2, -13}
};



void weighted_avarage(int width, height, orgColor[][height], edgedColor[][height])
{
  int weight = 0;
  for(int i = 1; i < width - 1; i++)
    for(int j = 1; j < height - 1; j++)
      edgedColor[i][j] = (orgColor[i-1][j-1] * nine[0][0] + orgColor[i][j-1] * nine[1][0] + orgColor[i+1][j-1] * nine[2][0]
      + orgColor[i-1][j] * nine[0][1] + orgColor[i][j] * nine[1][1] + orgColor[i+1][j] * nine[2][1]
      + orgColor[i-1][j+1] * nine[0][2] + orgColor[i][j+1] * nine[1][2] + orgColor[i+1][j+1] * nine[2][2]) / 9;
}
