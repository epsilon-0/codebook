#ifndef _NTT_
#define _NTT_

// Number Theoretic Transform
// Modular FFT and multiplication of polynomials

#include "nt.hh"

typedef long long ll;

// set these to appropriate values in contest
const int P = 663224321;
const int mod = 663224321;
const ll g = 3; // generator for cyclic group

void Add(ll &x, ll y) {
  x += y;
  if (x >= mod)
    x -= mod;
}

void Mul(ll &x, ll y) {
  x *= y;
  if (x >= mod)
    x %= mod;
}

ll qpow(ll a, ll b) {
  ll ret = 1;
  while (b) {
    if (b & 1)
      Mul(ret, a);
    b >>= 1;
    Mul(a, a);
  }
  return ret;
}

inline ll Inv(ll a) { return qpow(a, mod - 2); }

struct NTT {
  int rev[maxn], dig[maxn], N, L;

  void init_rev(int n) {
    for (N = 1, L = 0; N <= n; N <<= 1, L++)
      ;
    memset(dig, 0, sizeof(int) * (L + 1));
    for (int i = 0; i < N; i++) {
      rev[i] = 0;
      int len = 0;
      for (int t = i; t; t >>= 1)
        dig[len++] = t & 1;
      for (int j = 0; j < L; j++)
        rev[i] = (rev[i] << 1) | dig[j];
    }
  }

  void DFT(ll a[], int flag) {
    for (int i = 0; i < N; i++)
      if (i < rev[i])
        swap(a[i], a[rev[i]]);
    for (int l = 2; l <= N; l <<= 1) {
      ll wn;
      if (flag == 1)
        wn = qpow(g, (P - 1) / l);
      else
        wn = qpow(g, P - 1 - (P - 1) / l);
      for (int k = 0; k < N; k += l) {
        ll w = 1;
        ll x, y;
        for (int j = k; j < k + l / 2; j++) {
          x = a[j];
          y = a[j + l / 2] * w % P;
          a[j] = (x + y) % P;
          a[j + l / 2] = (x - y + P) % P;
          Mul(w, wn);
        }
      }
    }
    if (flag == -1) {
      ll inv = Inv(N);
      for (int i = 0; i < N; i++)
        a[i] = a[i] * inv % P;
    }
  }
} ntt;

void poly_inv(int deg, ll *a, ll *b, ll *c) {
  if (deg == 1) {
    b[0] = Inv(a[0]);
    return;
  }
  poly_inv((deg + 1) >> 1, a, b, c);
  ntt.init_rev(deg << 1);
  for (int i = 0; i < deg; i++)
    c[i] = a[i];
  for (int i = deg; i < ntt.N; i++)
    c[i] = 0;
  ntt.DFT(c, 1);
  ntt.DFT(b, 1);
  for (int i = 0; i < ntt.N; i++)
    b[i] = ((2LL - c[i] * b[i] % P) + P) % P * b[i] % P;
  ntt.DFT(b, -1);
  for (int i = deg; i < ntt.N; i++)
    b[i] = 0;
}

#endif // _NTT_
