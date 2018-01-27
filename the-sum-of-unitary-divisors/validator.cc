#include "testlib.h"
#include <cstdio>
#include <string>
#include <vector>

int main(int argc, char** argv) {
  registerValidation(argc, argv);
  int T = inf.readInt(1, 50000, "T");
  inf.readEoln();
  while (T--) {
    inf.readLong(1, 50000000000000ll, "n");
    inf.readEoln();
  }
  inf.readEof();
  return 0;
}
