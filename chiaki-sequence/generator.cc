#include "testlib.h"
#include <cassert>
#include <cmath>
#include <vector>
#include <numeric>

void gen(int n) {
  putchar('0' + rnd.next(1, 9));
  for (int i = 1; i < n; ++i) {
    putchar('0' + rnd.next(0, 9));
  }
  puts("");
}

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);
  int T = 1000;
  printf("%d\n", T);
  for (int i = 0; i < 99; ++i) {
    printf("%lld\n", rnd.next(1ll, 1000000000000000000ll));
  }
  for (int i = 0; i < 100; ++i) {
    gen(20);
    gen(30);
    gen(40);
    gen(50);
    gen(60);
    gen(70);
    gen(80);
    gen(90);
    gen(100);
  }
  for (int i = 0; i < 100; ++i) {
    putchar('9');
  }
  puts("");
  return 0;
}
