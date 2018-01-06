#include "testlib.h"
#include <cassert>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>

using pii = std::pair<int, int>;

std::vector<int> distribute(int sn, int min_n, int max_n) {
  std::vector<int> ns;
  while (sn >= min_n) {
    int n = rnd.next(min_n, std::min(max_n, sn));
    ns.push_back(n);
    sn -= n;
  }
  return ns;
}

template<typename Int>
std::vector<Int> random_subset(Int n, int k){
  assert(n >= k);
  std::set<Int> set;
  for (Int i = n - k; i < n; ++ i) {
    Int p = rnd.next(static_cast<Int>(0), i - 1);
    if (set.count(p)) {
      set.insert(i);
    } else {
      set.insert(p);
    }
  }
  std::vector<Int> result;
  for (auto elem : set) {
    result.push_back(elem);
  }
  return result;
}

int main(int argc, char** argv) {
  registerGen(argc, argv, 1);
  int min_n = atoi(argv[1]);
  int max_n = atoi(argv[2]);
  int X = atoi(argv[3]);
  int Y = atoi(argv[4]);
  assert(X <= Y);
  assert(X > 1);

  std::vector<pii> all;
  if (1ll * (Y - X + 1) * Y / 2 <= 2000000) {
    for (int r = X; r <= Y; ++r) {
      for (int l = 1; l < r; ++l) {
        all.emplace_back(l, r);
      }
    }
  }
  shuffle(all.begin(), all.end());
  auto ns = distribute(200000, min_n, max_n);
  printf("%d\n", (int)ns.size());
  for (auto &&n: ns) {
    if (!all.empty()) {
      auto idx = random_subset(all.size(), n);
      printf("%d\n", n);
      for (int i = 0; i < n; ++i) {
        printf("%d %d\n", all[idx[i]].first, all[idx[i]].second);
      }
    } else {
      std::vector<pii> v;
      for (int i = 1; i <= n * 20; ++i) {
        int r = rnd.next(X, Y);
        int l = rnd.next(1, r - 1);
        v.emplace_back(l, r);
      }
      sort(v.begin(), v.end());
      v.erase(unique(v.begin(), v.end()), v.end());
      shuffle(v.begin(), v.end());
      assert(v.size() >= n);
      printf("%d\n", n);
      for (int i = 0; i < n; ++i) {
        printf("%d %d\n", v[i].first, v[i].second);
      }
    }
  }
  return 0;
}
