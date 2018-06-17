#include "point.hh"
#include <bits/stdc++.h>

using namespace std;

bool convexHull_UL(vector<point> points, vector<point> &hull) {
  if (points.size() < 3) {
    hull.push_back(points[0]);
    hull.push_back(points[1]);
    hull.push_back(points[0]);
    return false;
  }

  sort(points.begin(), points.end(), xComp());
  hull.push_back(points[0]), hull.push_back(points[1]);

  for (int i = 2; i < points.size(); i++) {
    while (hull.size() >= 2 &&
           sideOfLine(hull[hull.size() - 2], points[i],
                      hull[hull.size() - 1]) == -1)
      hull.pop_back();
    hull.push_back(points[i]);
  }
  for (auto pt : hull)
    cout << pt << ",";
  cout << " " << endl;

  hull.push_back(points.size() - 2);
  for (int i = points.size() - 3, upper_size = points.size(); i >= 0; i--) {
    while (hull.size() > upper_size &&
           sideOfLine(hull[hull.size() - 2], points[i],
                      hull[hull.size() - 1]) == -1)
      hull.pop_back();
    hull.push_back(points[i]);
  }
  hull.pop_back();
  return true;
}

double perimeter(const vector<point> polygon) {
  double total = 0.0;
  for (int i = 0; i < polygon.size() - 1; i++)
    total += dist(polygon[i], polygon[(i + 1) % polygon.size()]);
  return total;
}

int main() {
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
    vector<point> hull;
    bool val = convexHull_UL(points, hull);

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
