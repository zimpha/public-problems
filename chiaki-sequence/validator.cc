#include "testlib.h"

#include <cstdio>
#include <string>
#include <vector>

int main(int argc, char** argv) {
  registerValidation(argc, argv);
  int T = inf.readInt(1, 1000, "T");
  inf.readEoln();
  while (T--) {
    std::string n = inf.readToken("[0-9]{1,100}", "n");
    inf.readEoln();
    ensuref(n[0] != '0', "leading zeros are not allowed");
  }
  inf.readEof();
  return 0;
}
