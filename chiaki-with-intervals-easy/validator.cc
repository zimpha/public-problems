#include "testlib.h"
#include <cstdio>
#include <string>
#include <vector>

int main(int argc, char** argv) {
  registerValidation(argc, argv);
  int T = inf.readInt(1, 200000, "T");
  inf.readEoln();
  while (T--) {
    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();
    std::set<std::pair<int, int>> iv;
    std::set<int> s;
    for (int i = 0; i < n; ++i) {
      int l = inf.readInt(1, 1000000000, format("l[%d]", i + 1));
      inf.readSpace();
      int r = inf.readInt(l + 1, 1000000000, format("r[%d]", i + 1));
      inf.readEoln();
      ensuref(!iv.count(std::make_pair(l, r)), "every two intervals are not the same");
      iv.emplace(l, r);
      s.emplace(r);
    }
    ensuref(s.size() <= 15, "the number of distinct r_i does not exceed 15");
  }
  inf.readEof();
  return 0;
}
