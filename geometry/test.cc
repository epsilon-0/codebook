#include "point.hh"
#include <iostream>

using namespace std;

int main() {
  point a(0, 0), b(1, 0), c(0, 1), d(1, 1), z;
  bool s = intersect(a, b, d, c, z);
  cout << s << " " << z << endl;
  point p(1, 0), q(0, 0), r(1, -1);
  cout << angle(p, q, r) << endl;
  cout << sideOfLine(a, d, b) << endl;
  cout << sideOfLine(a, d, c) << endl;
}
