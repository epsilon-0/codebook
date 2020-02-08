#ifndef _LCP_
#define _LCP_

#include <vector>

using namespace std;

// kasai algorithm
template <class T>
vector<int> lcp_array(const vector<T> &str, const vector<int> &suffixArray) {
  int n = str.size(), k = 0;
  vector<int> lcpArray(n, 0);
  vector<int> rank(n, 0);
  for (int i = 0; i < n; i++)
    rank[suffixArray[i]] = i;
  for (int i = 0; i < n; i++, k ? k-- : 0) {
    if (rank[i] == n - 1) {
      k = 0;
      continue;
    }
    int j = suffixArray[rank[i] + 1];
    while (i + k < n && j + k < n && str[i + k] == str[j + k])
      k++;
    lcpArray[rank[i]] = k;
  }
  return lcpArray;
}

#endif // _LCP_
