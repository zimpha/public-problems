#include "testlib.h"
#include <string>
#include <cassert>
#include <algorithm>

std::string gen(int n) {
  std::string s(n, '0');
  for (int i = 0; i < n; ++i) {
    s[i] = rnd.next(2) + '0';
  }
  return s;
}

std::string gc(const std::string &s) {
  std::string r = s;
  for (size_t i = 1; i < s.size(); ++i) {
    r[i] = ((s[i] - '0') ^ (s[i - 1] - '0')) + '0';
  }
  return r;
}

std::string tc(const std::string &s) {
  std::string r = s;
  int c = 0;
  for (int i = s.size() - 1; i >= 0; --i) {
    c += s[i] - '0';
    if (c % 2 == 0) r[i] = '0';
    else r[i] = '1';
    c += r[i] - '0';
    c /= 2;
  }
  return r;
}

int main(int argc, char **argv) {
  registerGen(argc, argv, 0);
  assert(argc >= 4);
  int min_n = std::atoi(argv[1]);
  int max_n = std::atoi(argv[2]);
  int marks = std::atoi(argv[3]);
  int N = 1000000;
  std::vector<int> ns;
  while (N >= min_n) {
    int n = rnd.next(min_n, std::min(max_n, N));
    ns.push_back(n);
    N -= n;
  }
  printf("%d\n", (int)ns.size());
  for (auto &&n: ns) {
    auto s = gen(n);
    auto g = gc(s);
    auto t = tc(s);
    int x = rnd.next(0, std::min(n, marks));
    int y = rnd.next(0, std::min(n, marks));
    for (int i = 0; i < x; ++i) {
      g[rnd.next(n)] = '?';
    }
    for (int i = 0; i < y; ++i) {
      t[rnd.next(n)] = '?';
    }
    if (!rnd.next(100)) {
      int x = rnd.next(n), y = rnd.next(n);
      std::swap(g[x], g[y]);
    }
    if (!rnd.next(100)) {
      int x = rnd.next(n), y = rnd.next(n);
      std::swap(t[x], t[y]);
    }
    puts(g.c_str());
    puts(t.c_str());
  }
  return 0;
}
