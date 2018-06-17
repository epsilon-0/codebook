#ifndef _POINT_INCLUDED_
#define _POINT_INCLUDED_
#include <complex>
#include <limits>

using namespace std;

typedef complex<double> point;
#define x(a) real(a)
#define y(a) imag(a)

const double eps = 1e-9;
const double pi = 2 * acos(0.0);
const double inf = numeric_limits<double>::max();

struct xComp {
  inline bool operator()(const point &a, const point &b) {
    if (fabs(a.x() - b.x()) < eps)
      return a.y() < b.y();
    return a.x() < b.x();
  }
};

struct yComp {
  inline bool operator()(const point &a, const point &b) {
    if (fabs(a.y() - b.y()) < eps)
      return a.x() < b.x();
    return a.y() < b.y();
  }
};

double dot(const point &a, const point &b) { return x(conj(a) * b); }

double cross(const point &a, const point &b) { return y(conj(a) * b); }

double length(const point &a) { return sqrt(dot(a, a)); }

void normalize(point &a) {
  double lgt = length(a);
  if (lgt > eps)
    a /= lgt;
}

double dist(const point &a, const point &b) { return length(a - b); }

double angle(const point &a, const point &b, const point &c) {
  // should check if none of the points are same before calling
  // Angle ABC
  double theta = arg(c - b) - arg(a - b);
  if (theta < 0)
    theta += 2.0 * pi;
  return theta;
}

point rotateAt(const point &a, const point &b, double t) {
  return a + (b - a) * polar(1.0, t);
}

point rotate(const point &a, double t) {
  return rotateAt(a, point(0.0, 0.0), t);
}

point reflect(const point &p, const point &a, const point &b) {
  point z = p - a;
  point w = b - a;
  return conj(z / w) * w + a;
}

bool intersect(const point &a, const point &b, const point &p, const point &q,
               point &z) {
  double d1 = cross(p - a, b - a);
  double d2 = cross(q - a, b - a);
  if (fabs(d1 - d2) < eps) {
    z = point(inf, inf);
    return false;
  }
  z = (d1 * q - d2 * p) / (d1 - d2);
  return true;
}

point projectAt(const point &p, const point &a, const point &b) {
  return a + (b - a) * dot(p - a, b - a) / length(b - a);
}

point project(const point &p, const point &a) {
  return projectAt(p, a, point(0.0, 0.0));
}

int sideOfLine(point &a, point &b, point &p) {
  double theta = angle(a, b, p);
  if (fabs(theta) < eps || fabs(theta-pi) < eps)
    return 0;
  else if (theta > pi)
    return 1; // to the left
  return -1;  // on the right
}

#endif // _POINT_INCLUDED_
