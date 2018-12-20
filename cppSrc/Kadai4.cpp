#include <iostream>
#include <vector>
#include <string>
#include "Pgm.h"

using namespace std;

int main(int argc, char const *argv[]) {

  int size;
  const string outFile = "../result/output.pgm";


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


  vector<int> orgColor(size);  // size分だけの配列を確保する



  pgm.setImageMatrix(orgColor);  // orgColorに読み込んだ画像データを書き込む

  pgm.writePgm(outFile, orgColor);  // outFileに画像データを出力




  return 0;
}
