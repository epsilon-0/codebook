#ifndef _POLYGON_
#define _POLYGON_

#include "point.hh"
#include <algorithm>
#include <vector>

using namespace std;

bool monotone_chain(vector<point> points, vector<point> &hull) {
  // assume that no three are collinear
  if (points.size() < 3) {
    hull.push_back(points[0]);
    hull.push_back(points[1]);
    hull.push_back(points[0]);
    return false;
  }

  sort(points.begin(), points.end(), xComp());

  for (int i = 0; i < points.size(); i++) {
    while (hull.size() >= 2 &&
           sideOfLine(hull[hull.size() - 2], points[i],
                      hull[hull.size() - 1]) <= 0)
      hull.pop_back();
    hull.push_back(points[i]);
  }

  for (int i = points.size() - 2, upper_size = hull.size() + 1; i >= 0; i--) {
    while (hull.size() >= upper_size &&
           sideOfLine(hull[hull.size() - 2], points[i],
                      hull[hull.size() - 1]) <= 0)
      hull.pop_back();
    hull.push_back(points[i]);
  }
  hull.pop_back();
  return true;
}

double perimeter(const vector<point> &polygon) {
  double total = 0.0;
  for (int i = 0; i < polygon.size(); i++)
    total += dist(polygon[i], polygon[(i + 1) % polygon.size()]);
  return total;
}

int is_convex(const vector<point> &polygon) {
  int conv, coll, conc;
  int n = polygon.size();
  for (int i = 0; i < n; i++) {
    double theta =
        angle(polygon[i], polygon[(i + 1) % n], polygon[(i + 2) % n]);
    if (fabs(theta - pi) < eps)
      coll++;
    else if (theta < pi)
      conv++;
    else
      conc++;
  }
  if (conc > 0)
    return -1;
  else if (coll > 0)
    return 0;
  return 1;
}

double trap(const point &a, const point &b) {
  return (b.x() - a.x()) * (b.y() + a.y()) / 2;
}

double area(const vector<point> &polygon) {
  double total = 0.0;
  int n = polygon.size();
  for (int i = 0; i < n; i++)
    total += trap(polygon[i], polygon[(i + 1) % n]);
  return fabs(total);
}

double triangle_area(const point &a, const point &b, const point &c) {
  return fabs(trap(a, b) + trap(b, c) + trap(c, a));
}

double height(const point &a, const point &b, const point &p) {
  return triangle_area(a, b, p) / dist(a, b) * 2.0;
}

#endif // _POLYGON_
