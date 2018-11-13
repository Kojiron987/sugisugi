#pragma once

#include <stdio.h>


void weighted_avarage(int width, int height, const int *orgColor, int *edgedColor);
void weighted_avarage_ver2(int width, int height, const int *orgColor, int *edgedColor);
void golay_filter(int colorSize, int width, int height, const int *orgColor, int *edgedColor);
void median_filter(int width, int height, const int *orgColor, int *edgedColor);
void mySort(int *arr, int lenght);
