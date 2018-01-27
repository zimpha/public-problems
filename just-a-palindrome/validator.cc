#include "testlib.h"

#include <cstdio>
#include <string>
#include <vector>

int main(int argc, char** argv) {
  registerValidation(argc, argv);
  int T = inf.readInt(1, 1000000, "T");
  inf.readEoln();
  int sn = 0;
  while (T--) {
    std::string s = inf.readToken("[a-zA-Z]{1,1000000}", "n");
    sn += s.size();
    inf.readEoln();
    ensuref(sn <= 1000000, "the sum of |s| does exceed 1000000");
  }
  inf.readEof();
  return 0;
}
