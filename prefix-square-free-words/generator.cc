#include "testlib.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>

int main(int argc, char **argv) {
  registerGen(argc, argv, 1);
  int T = std::atoi(argv[1]);
  int min_n = std::atoi(argv[2]);
  int max_n = std::atoi(argv[3]);
  printf("%d\n", T);
  for (int i = 0; i < T; ++i) {
    printf("%d %d\n", rnd.next(min_n, max_n), rnd.next(1, 1000000000));
  }
  return 0;
}
