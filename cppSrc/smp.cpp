#include <iostream>
#include <vector>


using namespace std;

int main(int argc, char const *argv[]) {

  vector<int> a(1);
  a[0] = 1;
  a[1] = 2;
  a[2] = 3;

  cout << a[2] << endl;

  return 0;
}
