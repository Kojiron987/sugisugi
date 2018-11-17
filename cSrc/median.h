#pragma once

#include <stdio.h>
/*
static const double nine_matrix[3][3];
static const double sixteen_matrix[3][3];
static const double Golay_matrix[5][5];
static const double laplacian_matrix[3][3];
static const double digital_laplacian_matrix[3][3];
static const double savitzky_matrix[5][5];
*/


void weighted_avarage(int width, int height, const int *orgColor, int *edgedColor);
void weighted_avarage_ver2(int width, int height, const int *orgColor, int *edgedColor);
void golay_filter(int colorSize, int width, int height, const int *orgColor, int *edgedColor);
void median_filter(int width, int height, const int *orgColor, int *edgedColor);
void mySort(int *arr, int lenght);  //バブルソート(手抜き)
void laplacian_filter(int colorSize, int width, int height, const int *orgColor, int *edgedColor);
void digital_laplacian_filter(int colorSize, int width, int height, const int *orgColor, int *edgedColor);
void savitzky_golay(int colorSize, int width, int height, const int *orgColor, int *edgedColor);
