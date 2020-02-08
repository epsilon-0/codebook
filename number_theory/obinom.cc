#include <bits/stdc++.h>
#include <chrono>

using namespace std::chrono;
using namespace std;

const int maxn = (int)(1 << 20) + 23;
const int mod = 998244353;
const int root = 15311432;
const int root_1 = 469870224;
const int root_pw = 1 << 23;

int inv[maxn], ifact[maxn], fact[maxn], rpow[maxn];

int inverse(int a) {
  return 1 < a ? mod - (1LL * inverse(mod % a) * ((int)mod / a) % mod) : 1;
}

inline int modular_power(int a, int n) {
  int ans = 1;
  while (n) {
    if (n & 1)
      ans = (int)(1LL * ans * a % mod);
    n >>= 1;
    a = (int)(1LL * a * a % mod);
  }
  return ans;
}

// invert tells us if we are doing inverse fft or not
// VERY IMPORTANT THAT SIZE OF a IS A POWER OF 2
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
    int n_1 = (n < maxn) ? inv[n] : inverse(n);
    for (int &x : a)
      x = (int)(1LL * x * n_1 % mod);
  }
}

// assuming they are of same size
vector<int> multiply(const vector<int> &a, const vector<int> &b) {
  vector<int> fa(a.begin(), a.end()), fb(b.begin(), b.end());
  int n = 1;
  while (n < a.size() + b.size())
    n <<= 1;
  //  cout << " power of 2 is " << n << endl;
  fa.resize(n);
  fb.resize(n);
  //  cout << "resized the vectors" << endl;
  ntt(fa, false);
  ntt(fb, false);
  //  cout << "computed the ntts" << endl;
  for (int i = 0; i < n; i++)
    fa[i] = (int)(1LL * fa[i] * fb[i] % mod);
  ntt(fa, true);
  while (fa[fa.size() - 1] == 0)
    fa.pop_back();
  return fa;
}

// given a_1, ..., a_n give back (x-a1)(x-a2)...(x-an)
vector<int> root_polynomial(int r) {
  queue<vector<int>> que;
  for (int i = 0; i < r; i++)
    que.push({(mod - i) % mod, 1});
  while (que.size() > 1) {
    auto a = que.front();
    que.pop();
    auto b = que.front();
    que.pop();
    que.push(multiply(a, b));
  }
  return que.front();
}

// given poly(x) calculate poly(x+k)
vector<int> polynomial_shift(const vector<int> poly, int k) {
  if (poly.size() <= 1)
    return poly;
  vector<int> kvec, coeff;
  int n = poly.size();
  //  cout << "doing calculation for " << n << endl;
  for (int i = n - 1; i > -1; i--)
    coeff.push_back((int)(1LL * fact[i] * poly[i] % mod));
  int kpow = 1;
  kvec.push_back(kpow);
  for (int i = 1; i < n; i++) {
    kpow = (int)(1LL * kpow * k % mod);
    kvec.push_back((int)(1LL * kpow * ifact[i] % mod));
  }
  //  cout << "calculated component vectors for " << n << endl;
  vector<int> convolution = multiply(kvec, coeff);
  //  cout << "did the convolution for " << n << endl;
  vector<int> answer(n, 0);
  for (int i = 0; i < n; i++)
    answer[i] = ((int)(1LL * convolution[n - 1 - i] * ifact[i] % mod));
  return answer;
}

vector<int> croot_polynomial(int r) {
  // gives back x(x-1)(x-2)(x-3)....(x-r+1)
  if (r == 1)
    return {0, 1};
  //  cout << "computing for " << r << endl;
  vector<int> recur_poly = croot_polynomial(r / 2);
  //  cout << "finished recur for " << r << endl;
  vector<int> shift_poly = polynomial_shift(recur_poly, mod - (r / 2));
  //  cout << "sizes: recur_poly: " << recur_poly.size()
  //       << "\tshif_poly: " << shift_poly.size() << endl;
  recur_poly = multiply(recur_poly, shift_poly);
  //  cout << "calculated most things for " << r << endl;
  if (r & 1) {
    recur_poly.insert(recur_poly.begin(), 0);
    int ss = mod - r + 1;
    for (int i = 0; i < recur_poly.size() - 1; i++) {
      recur_poly[i] =
          (int)(((long long)1LL * ss * recur_poly[i + 1] + recur_poly[i]) %
                mod);
    }
  }
  //  cout << r << " finishing up" << endl;
  return recur_poly;
}

const int maxt = 101;
int nn[maxt], pp[maxt], rr[maxt], anss[maxt];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  // needed for r!^(-1)
  inv[1] = ifact[0] = ifact[1] = fact[0] = fact[1] = rpow[0] = 1;
  rpow[1] = root_1;
  for (int i = 2; i < maxn; i++) {
    inv[i] = mod - (int)((1LL * inv[mod % i] * (mod / i)) % mod);
    ifact[i] = (int)(1LL * ifact[i - 1] * inv[i] % mod);
    fact[i] = (int)(1LL * fact[i - 1] * i % mod);
    rpow[i] = (int)(1LL * root_1 * rpow[i - 1] % mod);
  }

  //  cout << "starting " << endl;
  int t;
  cin >> t;

  vector<pair<int, int>> rvec;
  for (int i = 0; i < t; i++) {
    cin >> nn[i] >> pp[i] >> rr[i];
    rvec.push_back({rr[i], i});
  }
  sort(rvec.begin(), rvec.end());

  vector<int> rpoly = {0, 1}; // start with the linear polynomial
  int prev_r = 1;
  // cout << "doing test cases" << endl;
  for (int tt = 0; tt < t; tt++) {
    int tnum = rvec[tt].second;
    int n = nn[tnum], p = pp[tnum], r = rr[tnum];

    // cout << "starting poly compute" << endl;
    if (r > prev_r) {
      vector<int> npoly = croot_polynomial(r - prev_r);
      // cout << "done npoly " << npoly.size() << " " << r << endl;
      if (npoly.size() < rpoly.size())
        npoly = polynomial_shift(npoly, mod - rpoly.size() + 1);
      else
        rpoly = polynomial_shift(rpoly, mod - npoly.size() + 1);
      // cout << "shifted" << endl;
      rpoly = multiply(rpoly, npoly);
      prev_r = r;
    }
    // cout << "computed root poly" << endl;
    int answer = 0;
    int p_n_1 = modular_power(p, n + 1); // p^(n+1) (constant)
    int p_r = 1;                         // p^r (running)
    int p_r_n_1 = 1;                     // (p^(n+1))^r (running)
    for (int i = 0; i <= r; i++, p_r = (int)(1LL * p * p_r % mod)) {
      int geometric_sum = n + 1;
      if (p_r > 1) {
        int denom = inverse(p_r - 1);
        int numer = p_r_n_1 - 1;
        // int numer = modular_power(p_r, n+1) - 1;
        geometric_sum = (int)(1LL * denom * numer % mod);
      }
      p_r_n_1 = (int)(1LL * p_r_n_1 * p_n_1 % mod);
      //      cout << p_r_n_1 << endl;
      int factor = (int)(1LL * rpoly[i] * geometric_sum % mod);
      answer = (int)(((long long)answer + factor) % mod);
    }
    anss[tnum] = (int)(1LL * answer * ifact[r] % mod);
  }
  for (int tt = 0; tt < t; tt++)
    cout << anss[tt] << endl;
}
