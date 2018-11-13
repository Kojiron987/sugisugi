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

  int temp = 0;

  for(int j = 1; j < (height - 1); j++)
    for(int i = 1; i < (width -1); i++) {
      temp = 0;
      for(int j1=-1;j1<=1;j1++){
        for(int i1=-1;i1<=1;i1++){
          temp += sixteen[i1+1][j1+1]*orgColor[(j+j1) * width + (i+i1)];
        }
      }
      temp /= 16;
      edgedColor[j * width + i] = temp;
    }
}


void golay_filter(int colorSize, int width, int height, const int *orgColor, int *edgedColor)
{
  int temp = 0;
  for(int j = 2; j < (height - 2); j++)
    for(int i = 2; i < (width - 2); i++) {
      for(int j1=-1;j1<=1;j1++) {
        for(int i1=-1;i1<=1;i1++) {
            temp += Golay[i1+1][j1+1]*orgColor[(j+j1) * width + (i+i1)];
        }
      }
      temp /= 175;
      if(temp < 0)
        edgedColor[j * width + i] = 0;
      else if(temp > colorSize)
        edgedColor[j * width + i] = colorSize;
      else
        edgedColor[j * width + i] = temp;
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
    for(int j = 0; j < length; j++) {
      if(arr[i] < arr[j]) {
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
      }
    }
  }
}
