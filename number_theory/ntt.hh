#ifndef _NTT_
#define _NTT_

// Number Theoretic Transform
// Modular FFT and multiplication of polynomials

// credit: https://cp-algorithms.com/algebra/fft.html

#include <bits/stdc++.h>

using namespace std;

// calculates modular inverse
// also present in nt.hh
inline long long inverse(long long a, long long mod) {
  return 1 < a ? mod - inverse(mod % a, a) * mod / a : 1;
}

class NTT {
public:
  const int mod;     // = 7340033;     // the prime for doing calculations
  const int root;    // = 5;          // primitive root of unity
  const int root_1;  // = 4404020;  // inverse of the primitive root of unity
  const int root_pw; // = 1 << 20; // max power of 2 dividing mod-1

  NTT() : mod(7340033), root(5), root_1(4404020), root_pw(1 << 20) {}
  NTT(int mod, int root, int root_1, int root_pw)
      : mod(mod), root(root), root_1(root_1), root_pw(root_pw) {}

  // invert tells us if we are diong inverse fft or not
  void ntt(vector<int> &a, bool invert = false) {
    int n = a.size();
    // first calculate the bit reverse permutation
    // TODO: can we make this into a table that can be reused?
    // THAT IS THE WHOLE POINT OF MAKING THIS A CLASS
    for (int i = 1, j = 0; i < n; i++) {
      int bit = n >> 1;
      for (; j & bit; bit >>= 1)
        j ^= bit;
      j ^= bit;

      if (i < j)
        swap(a[i], a[j]);
    }

    // we are going down the recurrence tree
    // we need log2(n) iterations, done using len
    for (int len = 2; len <= n; len <<= 1) {
      int wlen = invert ? root_1 : root; // if we are doing inverse fft use the
                                         // root_1 as the point of calculation
      for (int i = len; i < root_pw; i <<= 1)
        // we need root^(n//len) as the calculation variable
        wlen = (int)(1LL * wlen * wlen % mod);

      // convolving and going up the recurrence tree
      for (int i = 0; i < n; i += len) {
        int w = 1;
        for (int j = 0; j < len / 2; j++) {
          int u = a[i + j], v = (int)(1LL * a[i + j + len / 2] * w % mod);
          a[i + j] = u + v < mod ? u + v : u + v - mod;
          a[i + j + len / 2] = u - v >= 0 ? u - v : u - v + mod;
          w = (int)(1LL * w * wlen % mod);
        }
      }
    }

    if (invert) {
      int n_1 = inverse(n, mod);
      for (int &x : a)
        x = (int)(1LL * x * n_1 % mod);
    }
  }
};

#endif // _NTT_
