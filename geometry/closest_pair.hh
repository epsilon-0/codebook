#ifndef _CLOSEST_PAIR_
#define _CLOSEST_PAIR_

#include "point.hh"
#include <algorithm>
#include <vector>

using namespace std;

typedef vector<point>::iterator ptIter;

void closest_pair_helper(ptIter start, ptIter end, ptIter temp, point &a,
                         point &b) {
  int n = end - start;
  if (n <= 20) {
    double minDist = inf;
    for (ptIter i = start; i != end; i++)
      for (ptIter j = i + 1; j != end; j++) {
        double currDist = dist(*i, *j);
        if (currDist < minDist) {
          minDist = currDist;
          a = *i;
          b = *j;
        }
      }
    sort(start, end, yComp());
    return;
  }
  ptIter mid = start + (n / 2);
  point la, lb, ra, rb;
  closest_pair_helper(start, mid, temp, la, lb);
  closest_pair_helper(mid, end, temp + (n / 2), ra, rb);
  merge(start, mid, mid, end, temp, yComp());
  copy(temp, temp + n, start);
  double stripSize;
  if (dist(la, lb) < dist(ra, rb))
    a = la, b = lb, stripSize = dist(la, lb);
  else
    a = ra, b = rb, stripSize = dist(ra, rb);
  double midX = (*mid).x();
  int cnt = 0;
  ptIter aux = temp;
  for (ptIter i = start; i != end; i++)
    if ((*i).x() >= midX - 2 * stripSize && (*i).x() <= midX + 2 * stripSize)
      *(aux++) = *i, cnt++;
  for (ptIter i = temp; i != temp + cnt; i++)
    for (ptIter j = i + 1; j != temp + cnt && (*j).y() - (*i).y() <= stripSize;
         j++) {
      double currDist = dist(*i, *j);
      if (currDist < stripSize) {
        stripSize = currDist;
        a = *i, b = *j;
      }
    }
}

void closest_pair(vector<point> points, point &a, point &b) {
  vector<point> temp(points.size(), point(0, 0));
  sort(points.begin(), points.end(), xComp());
  closest_pair_helper(points.begin(), points.end(), temp.begin(), a, b);
}

#endif // _CLOSEST_PAIR_
