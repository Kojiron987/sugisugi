#include <iostream>
#include <vector>
#include <algorithm>
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

  pgm.setImageMatrix(colorMatrix);

  /*    ２値化　その１     */
  /*-------------------------------------------------------------------*/
  const string outFile1 = "../result/threshold_1.pgm";
  const int BLACK = 0;
  const int WHITE = pgm.getColorSize();
  do{
    cout << "閾値を入力してください0 ~ " << pgm.getColorSize() << " : ";
    cin >> threshold;
  }while(threshold < 0 || threshold > pgm.getColorSize());

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
  vector<int> colorHist(pgm.getColorSize() + 1);
  array<int, 2> thresholdMode;



  pgm.setImageMatrix(colorMatrix);
  for(int i = 0; i < pgm.getHeight(); i++)
    for(int j = 0; j < pgm.getWidth(); j++) {
      index = colorMatrix[i*pgm.getWidth()+j];
      colorHist[index] += 1;
    }

                     // 目で見て峰を確認
    ofstream fOut(outHistFile);
    if(!fOut.is_open()) {
      cerr << "Failed to open " << outHistFile << endl;
      return 1;
    }

    for(int i = 0; i <= pgm.getColorSize(); i++)
      fOut << colorHist[i] << endl;
    fOut.close();


    auto point = max_element(begin(colorHist), end(colorHist));

    cout << *point << endl;;



  /*-------------------------------------------------------------------*/


  /*    ２値化　その３     */
  /*-------------------------------------------------------------------*/
  /*-------------------------------------------------------------------*/


  /*    ２値化　その４     */
  /*-------------------------------------------------------------------*/
  /*-------------------------------------------------------------------*/

  return 0;
}
