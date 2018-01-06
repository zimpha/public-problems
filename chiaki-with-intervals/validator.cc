#include "testlib.h"
#include <cstdio>
#include <string>
#include <vector>

int main(int argc, char** argv) {
  registerValidation(argc, argv);
  int T = inf.readInt(1, 200000, "T");
  inf.readEoln();
  int sum_n = 0;
  while (T--) {
    int n = inf.readInt(1, 200000, "n");
    inf.readEoln();
    std::set<std::pair<int, int>> iv;
    for (int i = 0; i < n; ++i) {
      int l = inf.readInt(1, 1000000000, format("l[%d]", i + 1));
      inf.readSpace();
      int r = inf.readInt(l + 1, 1000000000, format("r[%d]", i + 1));
      inf.readEoln();
      ensuref(!iv.count(std::make_pair(l, r)), "every two intervals are not the same");
      iv.emplace(l, r);
    }
    sum_n += n;
    ensuref(sum_n <= 200000, "sum of n in all test cases does not exceed 200000");
  }
  inf.readEof();
  return 0;
}
