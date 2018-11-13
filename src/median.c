#include "median.h"


void weighted_avarage(int width, int height, const int *orgColor, int *edgedColor)
{
  double nine[][3] = {
    {1.0 / 9.0,1.0/ 9.0 ,1.0 / 9.0},
    {1.0 / 9.0,1.0/ 9.0 ,1.0 / 9.0},
    {1.0 / 9.0,1.0/ 9.0 ,1.0 / 9.0}
  };

  int temp = 0;

  for(int j = 1; j < (height - 1); j++)
    for(int i = 1; i < (width -1); i++) {
      temp = 0;
      for(int j1=-1;j1<=1;j1++){
        for(int i1=-1;i1<=1;i1++){
            temp += nine[i1+1][j1+1]*orgColor[(j+j1) * width + (i+i1)];
        }
      }
      edgedColor[j * width + i] = temp;
    }
}

void weighted_avarage_ver2(int width, int height, const int *orgColor, int *edgedColor)
{
  double sixteen [][3] = {
    {1.0/16, 2.0/16, 1.0/16},
    {2.0/16, 4.0/16, 2.0/16},
    {1.0/16, 2.0/16, 1.0/16}
  };

  int temp = 0;

  for(int j = 1; j < (height - 1); j++)
    for(int i = 1; i < (width -1); i++) {
      temp = 0;
      for(int j1=-1;j1<=1;j1++){
        for(int i1=-1;i1<=1;i1++){
          temp += sixteen[i1+1][j1+1]*orgColor[(j+j1) * width + (i+i1)];
        }
      }
      edgedColor[j * width + i] = temp;
    }
}


void golay_filter(int colorSize, int width, int height, const int *orgColor, int *edgedColor)
{
  double Golay[][5] = {
    {-13.0/175, 2.0/175, 7.0/175, 2.0/175, -13.0/175},
    {2.0/175, 17.0/175, 22.0/175, 17.0/175, 2.0/175},
    {7.0/175, 22.0/175, 27.0/175, 22.0/175, 7.0/175},
    {2.0/175, 17.0/175, 22.0/175, 17.0/175, 2.0/175},
    {-13.0/175, 2.0/175, 7.0/175, 2.0/175, -13.0/175}
  };

  int temp = 0;
  for(int j = 2; j < (height - 2); j++)
    for(int i = 2; i < (width - 2); i++) {
      for(int j1=-2;j1<=2;j1++) {
        for(int i1=-2;i1<=2;i1++) {
            temp += (int)(Golay[i1+2][j1+2]*orgColor[(j+j1) * width + (i+i1)]);
        }
      }
      if(temp < 0)
        edgedColor[j * width + i] = 0;
      else if(temp > colorSize)
        edgedColor[j * width + i] = colorSize;
      else
        edgedColor[j * width + i] = temp;
      temp = 0;
    }
}

void median_filter(int width, int height, const int *orgColor, int *edgedColor)
{
  const int MEDIAN_AREA = 9;
  const int MEDIAN_POINT = 4;
  int median_array[MEDIAN_AREA];
  int median_index = 0;



  for(int j = 1; j < height-1; j++) {
    for(int i = 1; i < width-1; i++) {
      median_index = 0;
      for(int j1=-1;j1<=1;j1++) {
        for(int i1=-1;i1<=1;i1++) {
          median_array[median_index] = orgColor[(j+j1) * width + (i+i1)];
          median_index++;
        }
      }
      mySort(median_array, MEDIAN_AREA);
      edgedColor[j*width+i] = median_array[MEDIAN_POINT];
    }
  }
}





void mySort(int *arr, int length)
{
  int temp = 0;
  for(int i = 0; i < length; i++) {
    for(int j = length - 1; j > i; j--) {
      if(arr[j] < arr[j-1]) {
        temp = arr[j-1];
        arr[j-1] = arr[j];
        arr[j] = temp;
      }
    }
  }
}

void laplacian_filter(int colorSize, int width, int height, const int *orgColor, int *edgedColor)
{
  double laplacian_matrix[][3] = {
    {0.0, 1.0, 1.0},
    {1.0, -4.0, 1.0},
    {0.0, 1.0, 0.0}
  };
  int temp = 0;
  for(int j = 1; j < (height -1); j++)
    for(int i = 1; i < (width -1); i++) {
      temp = (int)(
        orgColor[(j-1)*width+i] * laplacian_matrix[1][0]
      + orgColor[j*width+(i-1)] * laplacian_matrix[0][1]
      + orgColor[j*width+i]     * laplacian_matrix[1][1]
      + orgColor[j*width+(i+1)] * laplacian_matrix[2][1]
      + orgColor[(j+1)*width+i] * laplacian_matrix[1][2]
      );
      if(temp < 0) {
        temp = 0;
      }
      else if(temp > colorSize) {
        temp = colorSize;
      }
      edgedColor[j*width+i] = temp;
    }

}



void digital_laplacian_filter(int colorSize, int width, int height, const int *orgColor, int *edgedColor)
{
  double digital_laplacian_matrix[][3] = {
    {1.0, 1.0, 1.0},
    {1.0, -8.0, 1.0},
    {1.0, 1.0, 1.0}
  };
  int temp = 0;
  for(int j = 1; j < (height -1); j++)
    for(int i = 1; i < (width -1); i++) {
      temp = (int)(
        orgColor[(j-1)*width+(i-1)] * digital_laplacian_matrix[0][0]
      + orgColor[(j-1)*width+i]     * digital_laplacian_matrix[1][0]
      + orgColor[(j-1)*width+(i+1)] * digital_laplacian_matrix[2][0]
      + orgColor[j*width+(i-1)]     * digital_laplacian_matrix[0][1]
      + orgColor[j*width+i]         * digital_laplacian_matrix[1][1]
      + orgColor[j*width+(i+1)]     * digital_laplacian_matrix[2][1]
      + orgColor[(j+1)*width+(i-1)] * digital_laplacian_matrix[0][2]
      + orgColor[(j+1)*width+i]     * digital_laplacian_matrix[1][2]
      + orgColor[(j+1)*width+(i+1)] * digital_laplacian_matrix[2][2]
      );
      if(temp < 0) {
        temp = 0;
      }
      else if(temp > colorSize) {
        temp = colorSize;
      }
      edgedColor[j*width+i] = temp;
    }

}



void savitzky_golay(int colorSize, int width, int height, const int *orgColor, int *edgedColor)
{
  double savitzky[][5] = {
    {4.0, 1.0, 0.0, 1.0, 4.0},
    {1.0, -2.0, -3.0, -2.0, 1.0},
    {0.0, -3.0, -4.0, -3.0, 0.0},
    {1.0, -2.0, -3.0, -2.0, 1.0},
    {4.0, 1.0, 0.0, 1.0, 4.0}
  };

  int temp = 0;
  for(int j = 2; j < (height - 2); j++)
    for(int i = 2; i < (width - 2); i++) {
      for(int j1=-2;j1<=2;j1++) {
        for(int i1=-2;i1<=2;i1++) {
            temp += (int)(savitzky[i1+2][j1+2]*orgColor[(j+j1) * width + (i+i1)]);
        }
      }
      if(temp < 0)
        edgedColor[j * width + i] = 0;
      else if(temp > colorSize)
        edgedColor[j * width + i] = colorSize;
      else
        edgedColor[j * width + i] = temp;
      temp = 0;
    }
}
