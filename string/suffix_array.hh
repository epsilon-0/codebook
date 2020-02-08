#ifndef _SUFFIX_ARRAY_
#define _SUFFIX_ARRAY_

#include <vector>

using namespace std;

template <class T> struct suffixData {
  int index;
  pair<int, int> rank;
  bool operator<(const suffixData &other) { return rank < other.rank; }
};

template <class T> vector<int> suffix_array(const vector<T> &str) {
  int n = str.size();
  suffixData<T> suffixes[n];
  for (int i = 0; i < n; i++) {
    suffixes[i].index = i;
    suffixes[i].rank.first = str[i];
    suffixes[i].rank.second = ((i + 1) < n) ? (str[i + 1]) : -1;
  }
  sort(suffixes, suffixes + n);
  int indices[n];
  for (int k = 4; k < 2 * n; k = k * 2) {
    int rank = 0;
    int prev_rank = suffixes[0].rank.first;
    suffixes[0].rank.first = rank;
    indices[suffixes[0].index] = 0;
    for (int i = 1; i < n; i++) {
      if (suffixes[i].rank.first == prev_rank &&
          suffixes[i].rank.second == suffixes[i - 1].rank.second) {
        prev_rank = suffixes[i].rank.first;
        suffixes[i].rank.first = rank;
      } else {
        prev_rank = suffixes[i].rank.first;
        suffixes[i].rank.first = ++rank;
      }
      indices[suffixes[i].index] = i;
    }
    for (int i = 0; i < n; i++) {
      int nextindex = suffixes[i].index + k / 2;
      suffixes[i].rank.second =
          (nextindex < n) ? suffixes[indices[nextindex]].rank.first : -1;
    }
    sort(suffixes, suffixes + n);
  }
  vector<int> suffixArray(n, 0);
  for (int i = 0; i < n; i++)
    suffixArray[i] = suffixes[i].index;
  return suffixArray;
}

#endif // _SUFFIX_ARRAY_
