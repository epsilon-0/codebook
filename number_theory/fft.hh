#ifndef _FFT_
#define _FFT_

#include <cmath>
#include <complex>
#include <vector>

using namespace std;

typedef complex<double> point;
const double pi = 3.14159265358979323846264338327950288419716939937510582;

// evaluate vector a on the n complex roots of unity
void fft(vector<point> &a, bool invert) {
  // invert tells to calculate the inverse fft
  int n = a.size();

  for (int i = 1, j = 0; i < n; i++) {
    int bit = n >> 1;
    for (; j >= bit; bit >>= 1)
      j -= bit;
    j += bit;
    if (i < j)
      swap(a[i], a[j]);
  }

  for (int len = 2; len <= n; len <<= 1) {
    double ang = (2.0 * pi / len) * (invert ? -1 : 1);

    point mul_factor(cos(ang), sin(ang));

    for (int i = 0; i < n; i += len) {
      point now(1, 0);

      for (int j = 0; j < len / 2; j++) {
        point u = a[i + j], v = a[i + j + len / 2] * now;

        a[i + j] = u + v;
        a[i + j + len / 2] = u - v;
        now *= mul_factor;
      }
    }
  }

  if (invert) {
    for (int i = 0; i < n; i++) {
      a[i] /= point(n, 0);
    }
  }
}

#endif // _FFT_
