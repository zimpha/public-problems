#include "testlib.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>

int main(int argc, char **argv) {
  registerGen(argc, argv, 1);
  int T = std::atoi(argv[1]);
  auto min_n = std::atoll(argv[2]);
  auto max_n = std::atoll(argv[3]);
  printf("%d\n", T);
  for (int i = 0; i < T; ++i) {
    printf("%lld\n", rnd.next(min_n, max_n));
  }
  return 0;
}
