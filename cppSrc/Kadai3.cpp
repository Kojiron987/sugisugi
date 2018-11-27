#include <iostream>
#include <vector>
#include <numeric>
#include <fstream>
#include <array>
#include "Pgm.h"

using namespace std;

int main(int argc, char const *argv[]) {
  int size, threshold, index;


  if(argc != 2) {
    cerr << "Usage: $ " << argv[0] << " Filename" << endl;
    return 1;
  }

  Pgm pgm;
  pgm.init(argv[1]);

  if(!pgm.is_openSucceed()) {
    cerr << "Failed to read pgm token." << endl;
    return 1;
  }

  cout << pgm << endl;

  size = pgm.getWidth() * pgm.getHeight();

  vector<int> colorMatrix(size);

  const int BLACK = 0;
  const int WHITE = pgm.getColorSize();
  const int COLORSIZE = pgm.getColorSize();


  /*    ２値化　その１     */
  /* 手動で閾値を決める */
  /*-------------------------------------------------------------------*/
  const string outFile1 = "../result/threshold_1.pgm";

  threshold = 0;
  pgm.setImageMatrix(colorMatrix);


  do{
    cout << "閾値を入力してください0 ~ " << COLORSIZE << " : ";
    cin >> threshold;
  }while(threshold < 0 || threshold > COLORSIZE);

  for(int i = 0; i < pgm.getHeight(); i++)
    for(int j = 0; j < pgm.getWidth(); j++) {
      index = i*pgm.getWidth()+j;
      if(colorMatrix[index] < threshold) {
        colorMatrix[index] = BLACK;
      }
      else {
        colorMatrix[index] = WHITE;
      }
    }

  pgm.writePgm(outFile1, colorMatrix);
  /*-------------------------------------------------------------------*/

  /*    ２値化　その２     */
  /*-------------------------------------------------------------------*/
  const string outHistFile = "../result/hist.txt";
  const string outFile2 = "../result/threshold_2.pgm";

  /*-------------------------------------------------------------------*/


  /*    ２値化　その３     */
  /* 判別分析法で閾値を求める */
  /*-------------------------------------------------------------------*/
  const string outFile3 = "../result/threshold_3.pgm";

  double median1, median2;
  double sum_of_color1, sum_of_color2;
  double max = 0.0, temp;
  vector<int> colorHist(COLORSIZE+1);

  threshold = 0;                                      // 要素の初期化
  pgm.setImageMatrix(colorMatrix);

  for(int i = 0; i < pgm.getHeight(); i++)            // ヒストグラムの作成
    for(int j = 0; j < pgm.getWidth(); j++) {
      index = colorMatrix[i*pgm.getWidth()+j];
      colorHist[index] += 1;
    }

  for(int i = 1; i < COLORSIZE; i++) {                           // 閾値を求める
    sum_of_color1 = accumulate(begin(colorHist), begin(colorHist)+i-1, 0.0);
    sum_of_color2 = accumulate(begin(colorHist)+i+1, end(colorHist), 0.0);
    median1 = sum_of_color1 / (i);
    median2 = sum_of_color2 / (COLORSIZE-i);
    temp = sum_of_color1 * sum_of_color2 * (median1 - median2) * (median1 - median2);
    if(max < temp) {
      max = temp;
      threshold = i;
    }
  }

  cout << "閾値は " << threshold << " になりました" << endl;

  for(int i = 0; i < pgm.getHeight(); i++)            // 画像の２値化をする
    for(int j = 0; j < pgm.getWidth(); j++) {
      index = i*pgm.getWidth()+j;
      if(colorMatrix[index] < threshold) {
        colorMatrix[index] = BLACK;
      }
      else {
        colorMatrix[index] = WHITE;
      }
    }

  pgm.writePgm(outFile3, colorMatrix);



  /*-------------------------------------------------------------------*/


  /*    ２値化　その４     */
  /*-------------------------------------------------------------------*/
  /*-------------------------------------------------------------------*/

  return 0;
}
