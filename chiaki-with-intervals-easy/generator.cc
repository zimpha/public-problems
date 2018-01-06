#include "testlib.h"
#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>

using pii = std::pair<int, int>;

int main(int argc, char** argv) {
  registerGen(argc, argv, 1);
  int T = atoi(argv[1]);
  int min_n = atoi(argv[2]);
  int max_n = atoi(argv[3]);
  int m = atoi(argv[4]);
  int X = atoi(argv[5]);
  int Y = atoi(argv[6]);
  assert(m <= 15);
  assert(X <= Y);
  assert(X > 1);
  printf("%d\n", T);
  for (int cas = 1; cas <= T; ++cas) {
    std::vector<pii> v;
    int n = rnd.next(min_n, max_n);
    for (int j = 0; j < m; ++j) {
      int r = rnd.next(X, Y);
      for (int i = 1; i <= n; ++i) {
        int l = rnd.next(1, r - 1);
        v.emplace_back(l, r);
      }
    }
    std::sort(v.begin(), v.end());
    v.erase(std::unique(v.begin(), v.end()), v.end());
    shuffle(v.begin(), v.end());
    assert(v.size() >= n);
    printf("%d\n", n);
    for (int i = 0; i < n; ++i) {
      printf("%d %d\n", v[i].first, v[i].second);
    }
  }
  return 0;
}
