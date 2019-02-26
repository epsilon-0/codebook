#ifndef _NTT_
#define _NTT_

// Number Theoretic Transform
// Modular FFT and multiplication of polynomials

#include "nt.hh"
#include <bits/stdc++.h>

// set these to appropriate values in contest
const long long P = 663224321;
const long long MOD = 663224321;
const long long g = 3; // generator for cyclic group

void ntt(vector<long long> &a, bool invert) {
  // invert tells to calculate the inverse fft
  int n = a.size();
  // apply the reverse bit permutation
  for (int i = 1, j = 0; i < n; i++) {
    int bit = n >> 1;
    for (; j >= bit; bit >>= 1)
      j -= bit;
    j += bit;
    if (i < j)
      swap(a[i], a[j]);
  }

  for (int len = 2; len <= n; len <<= 1) {
    long long mul_factor = modPow<long long>(g, len, MOD);
    for (int i = 0; i < n; i += len) {
      long long now = 1;
      for (int j = 0; j < len / 2; j++) {
        long long u = a[i + j], v = (a[i + j + len / 2] * now) % MOD;
        a[i + j] = (u + v) % MOD;
        a[i + j + len / 2] = (u - v + MOD) % MOD;
        now = (now * mul_factor) % MOD;
      }
    }
  }

  long long inv = inverse(n, MOD);
  if (invert) {
    for (int i = 0; i < n; i++) {
      a[i] = (a[i] * inv) % MOD;
    }
  }
}

#endif // _NTT_
