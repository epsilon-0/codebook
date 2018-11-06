#ifndef _NT_
#define _NT_

#include <map>
#include <set>

using namespace std;

const int maxn = (int)(1e5) + 10;
const long long MOD = (1e9) + 7;

inline long long gcd(long long a, long long b) {
  return (b == 0) ? a : gcd(b, a % b);
}

inline long long inverse(long long a, long long mod) {
  return 1 < a ? mod - inverse(mod % a, a) * mod / a : 1;
}

template <class num_t = long long>
inline num_t modPow(num_t a, num_t n, num_t mod) {
  num_t ans = 1;
  while (n) {
    if (n & 1)
      ans = (ans * a) % mod;
    n >>= 1;
    a = (a * a) % mod;
  }
  return ans;
}

long long choose[maxn][maxn] = {0};
void chooseINIT() {
  for (int i = 0; i < maxn; i++)
    choose[i][0] = choose[i][i] = 1;
  for (int i = 0; i < maxn; i++)
    for (int j = 1; j < i; j++) {
      choose[i][j] = (choose[i - 1][j] + choose[i - 1][j - 1]) % (MOD - 1);
    }
}

int spf[maxn] = {0};
void sieve() {
  spf[1] = 1;
  for (int i = 2; i < maxn; i++)
    spf[i] = i;
  for (int i = 4; i < maxn; i += 2)
    spf[i] = 2;
  for (int i = 3; i * i < maxn; i++) {
    if (spf[i] == i) {
      for (int j = i * i; j < maxn; j += i)
        if (spf[j] == j)
          spf[j] = i;
    }
  }
}

set<int> facs[maxn];
set<int> factorization(int n) {
  if (facs[n].size() == 0) {
    set<int> factors;
    factors.insert(1);
    if (n == 1)
      return factors;
    set<int> recFactors = factorization(n / spf[n]);
    for (int f : recFactors) {
      factors.insert(f);
      factors.insert(f * spf[n]);
    }
    facs[n] = factors;
  }
  return facs[n];
}

map<int, int> prime_factorization(int n) {
  map<int, int> pFactors;
  if (n == 1)
    return pFactors;
  int p = spf[n], k = n;
  while (k % spf[n] == 0) {
    k /= spf[n];
    pFactors[spf[n]]++;
  }
  map<int, int> recFactors = prime_factorization(k);
  for (auto it : recFactors)
    pFactors[it.first] = it.second;
  return pFactors;
}

#endif // _NT_
