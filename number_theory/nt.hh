#ifndef _NT_
#define _NT_

const long long MOD = (1e9) + 7;

template <class num_t = long long> inline num_t gcd(num_t a, num_t b) {
  return (b == 0) ? a : gcd(b, a % b);
}

template <class num_t = long long> inline num_t inverse(num_t a, num_t mod) {
  return 1 < a ? mod - inverse(mod % a, a) * mod / a : 1;
}

template <class num_t = long long>
inline num_t modPow(num_t a, num_t n, num_t mod) {
  if (n == 0)
    return 1;
  num_t ans = modPow(a, n / 2, mod);
  ans = (ans * ans) % mod;
  if (n & 1)
    ans = (ans * a) % mod;
  return ans;
}

long long choose[5005][5005] = {0};
void chooseINIT() {
  for (int i = 0; i < 5001; i++)
    choose[i][0] = choose[i][i] = 1;
  for (int i = 0; i < 5001; i++)
    for (int j = 1; j < i; j++) {
      choose[i][j] = (choose[i - 1][j] + choose[i - 1][j - 1]) % (MOD - 1);
    }
}

#endif // _NT_
