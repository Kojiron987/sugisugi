#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char const *argv[]) {

  ifstream fin("./smp.txt");
  char c;
  int i;

  if(!fin.is_open()) {
    cerr << "Failed to open" << "./smp.txt" << endl;
    return 1;
  }

  while(!fin.eof()) {
    i = fin.get();
    cout << (char)i;
  }

  fin.close();


  return 0;
}
