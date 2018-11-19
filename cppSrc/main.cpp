#include <iostream>
#include <array>
#include <algorithm>
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

  Pgm pgm(argv[1]);
  pgm.init();

  if(!pgm.is_openSucceed()) {
    cerr << "Failed to read pgm token." << endl;
    return 1;
  }

  cout << pgm << endl;

  size = pgm.getWidth() * pgm.getHeight();


  vector<int> orgColor(size);



  pgm.setImageMatrix(orgColor);

  pgm.writePgm(outFile, orgColor);


  return 0;
}
