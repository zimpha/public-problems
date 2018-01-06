#include "testlib.h"
#include <cstdio>
#include <string>
#include <vector>

int main(int argc, char** argv) {
  registerValidation(argc, argv);
  int T = inf.readInt(1, 100, "T");
  inf.readEoln();
  while (T--) {
    int n = inf.readInt(1, 100, "n");
    inf.readSpace();
    int m = inf.readInt(1, 1000000000, "m");
    inf.readEoln();
  }
  inf.readEof();
  return 0;
}
