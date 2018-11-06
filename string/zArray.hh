#ifndef _Z_ARRAY_
#define _Z_ARRAY_

void getZarr(char *str, int *Z, int n) {
  int L, R, k;
  L = R = 0;
  for (int i = 1; i < n; ++i) {
    if (i > R) {
      L = R = i;
      while (R < n && str[R - L] == str[R])
        R++;
      Z[i] = R - L;
      R--;
    } else {
      k = i - L;
      if (Z[k] < R - i + 1)
        Z[i] = Z[k];
      else {
        L = i;
        while (R < n && str[R - L] == str[R])
          R++;
        Z[i] = R - L;
        R--;
      }
    }
  }
}

#endif // _Z_ARRAY_
