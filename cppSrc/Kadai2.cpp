#include <iostream>
#include <string>
#include <cstdlib>

#include "median.h"
#include "Pgm.h"

using namespace std;

int main(int argc, const char* argv[])
{
  int filter_flag, size;
  int *orgColor, *edgedColor;
  const string outFile = "../result/filtered.pgm";


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

  edgedColor = new int[size];
  orgColor = new int[size];


  pgm.setImageMatrix(orgColor);


  // 使うフィルタの選択

  cout << "フィルタの選択\n1: 平滑フィルタ9\n2: 平滑フィルタ16\n3: Golayフィルタ\n4: 平均化フィルタ\n";
  cout << "5: ラプラシアン\n6: デジタルラプラシアン\n7: Savitzky-Golay\n> ";
  cin >> filter_flag;

  switch (filter_flag) {
  case 1:
    weighted_avarage(pgm.getWidth(), pgm.getHeight(), orgColor, edgedColor);
    break;
  case 2:
    weighted_avarage_ver2(pgm.getWidth(), pgm.getHeight(), orgColor, edgedColor);
    break;
  case 3:
    golay_filter(pgm.getColorSize(), pgm.getWidth(), pgm.getHeight(), orgColor, edgedColor);
    break;
  case 4:
    median_filter(pgm.getWidth(), pgm.getHeight(), orgColor, edgedColor);
    break;
  case 5:
    laplacian_filter(pgm.getColorSize(), pgm.getWidth(), pgm.getHeight(), orgColor, edgedColor);
    break;
  case 6:
    digital_laplacian_filter(pgm.getColorSize(), pgm.getWidth(), pgm.getHeight(), orgColor, edgedColor);
    break;
  case 7:
    savitzky_golay(pgm.getColorSize(), pgm.getWidth(), pgm.getHeight(), orgColor, edgedColor);
    break;
  default:
    printf("不正な入力です\n");
    exit(1);
    break;
  }


  // フィルタを通した画像データの出力
  pgm.writePgm(outFile, edgedColor);
  // メモリの開放
  delete [] orgColor;
  delete [] edgedColor;

  return 0;

}
