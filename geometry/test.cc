#include "point.hh"
#include "polygon.hh"

#include <bits/stdc++.h>

using namespace std;

int main() {
  point a(0, 0), b(1, 0), c(0, 1), d(1, 1), z;
  bool s = do_segments_intersect(a, d, c, c);
  cout << s << endl;
  point p(1, 0), q(0, 0), r(1, -1);
  cout << angle(p, q, r) << endl;
  cout << sideOfLine(a, d, b) << endl;
  cout << sideOfLine(a, d, c) << endl;
  cout << angle(a, a, b) << endl;
}
