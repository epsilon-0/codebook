#include "point.hh"
#include "polygon.hh"

#include <bits/stdc++.h>

using namespace std;

int main() {
  /*
  point a(0, 0), b(1, 0), c(0, 1), d(1, 1), z;
  bool s = intersect(a, b, d, c, z);
  cout << s << " " << z << endl;
  point p(1, 0), q(0, 0), r(1, -1);
  cout << angle(p, q, r) << endl;
  cout << sideOfLine(a, d, b) << endl;
  cout << sideOfLine(a, d, c) << endl;
  cout << angle(a, a, b) << endl;
  */
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<point> points;
    for (int i = 0; i < n; i++) {
      double x, y;
      cin >> x >> y;
      points.push_back(point(x, y));
    }
    sort(points.begin(), points.end(), xComp());
    points.erase(unique(points.begin(), points.end()), points.end());
    for (auto p : points)
      cout << p << endl;
    vector<point> hull;
    bool val = convexHull_MC(points, hull);

    if (!val) {
      cout << -1 << endl;
      continue;
    }
    sort(hull.begin(), hull.end(), xComp());
    int i;
    for (i = 0; i < hull.size() - 1; i++)
      cout << hull[i].x() << " " << hull[i].y() << ", ";
    cout << hull[i].x() << " " << hull[i].y() << endl;
  }
}
