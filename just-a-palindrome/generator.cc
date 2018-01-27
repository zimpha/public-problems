#include "testlib.h"
#include <string>
#include <cassert>
#include <algorithm>

char sigma[52];

std::string genpali(int len) {
  std::string ret = "";
  if (len & 1) ret = ret + sigma[rnd.next(52)];
  for (int i = 0; i < len / 2; ++ i) {
    int t = rnd.next(52);
    ret = sigma[t] + ret + sigma[t];
  }
  return ret;
}

std::string genstr(std::string ret, int len) {
  int extra = len - ret.size();
  assert(extra <= len && extra >= 0);
  if (extra == 0) return ret;
  int a = rnd.next(extra), b = extra - a;
  for (int i = 0; i < a; ++ i) {
    ret = sigma[rnd.next(52)] + ret;
  }
  for (int i = 0; i < b; ++ i) {
    ret = ret + sigma[rnd.next(52)];
  }
  assert(ret.size() == len);
  return ret;
}

void gen1(int n) {
  for (int i = 0; i < n; ++ i) {
    int t = rnd.next(52);
    putchar(sigma[t]);
  }
  puts("");
}

void gen2(int n) {
  int b = rnd.next(1, (int)sqrt(n));
  int lm = n / b;
  assert(lm * b <= n);
  std::string ret = "";
  for (int i = 0; i < b; ++ i) {
    int len = rnd.next(1, lm);
    std::string tmp = genpali(len);
    ret += genstr(tmp, lm);
  }
  ret = genstr(ret, n);
  puts(ret.c_str());
}

void gen3(int n) {
  int b = rnd.next(1, (int)sqrt(n));
  int lm = n / b;
  assert(lm * b <= n);
  std::string ret = "";
  for (int i = 0; i < b; ++ i) {
    int len = rnd.next(lm / 2) + lm / 2;
    std::string tmp = genpali(len);
    ret += genstr(tmp, lm);
  }
  ret = genstr(ret, n);
  for (int _ = 0; _ < 10; ++ _) {
    int i = rnd.next(n), j = rnd.next(n);
    std::swap(ret[i], ret[j]);
  }
  assert(ret.size() == n);
  puts(ret.c_str());
}

void gen4(int n) {
  int b = rnd.next(1, (int)sqrt(n));
  int lm = n / b;
  assert(lm * b <= n);
  std::string ret = "";
  for (int i = 0; i < b; ++ i) {
    int len = rnd.next(lm / 2) + (lm / 2);
    std::string tmp = genpali(len);
    int p1, p2;
    do {
      p1 = rnd.next(tmp.size());
      p2 = rnd.next(tmp.size());
    } while (p1 == p2);
    int t = rnd.next(4);
    if (t == 0) {
      std::swap(tmp[p1], tmp[p2]);
    } else if (t == 1) {
      tmp[p1] = sigma[rnd.next(52)];
    } else if (t == 2) {
      tmp[p2] = sigma[rnd.next(52)];
    } else if (t == 3) {
      tmp[p1] = sigma[rnd.next(52)];
      tmp[p2] = sigma[rnd.next(52)];
    }
    ret += genstr(tmp, lm);
  }
  ret = genstr(ret, n);
  for (int _ = 0; _ < 10; ++ _) {
    int i = rnd.next(n), j = rnd.next(n);
    std::swap(ret[i], ret[j]);
  }
  puts(ret.c_str());
}

void gen5(int n) {
  int b = rnd.next(1, (int)sqrt(sqrt(n)));
  int lm = n / b;
  assert(lm * b <= n);
  std::string ret = "";
  for (int i = 0; i < b; ++ i) {
    int len = rnd.next(lm / 2) + (lm / 2);
    std::string tmp = genpali(len);
    tmp =  genstr(tmp, lm);
    int p1, p2;
    do {
      p1 = rnd.next(tmp.size());
      p2 = rnd.next(tmp.size());
    } while (p1 == p2);
    int t = rnd.next(4);
    if (t == 0) {
      std::swap(tmp[p1], tmp[p2]);
    } else if (t == 1) {
      tmp[p1] = sigma[rnd.next(52)];
    } else if (t == 2) {
      tmp[p2] = sigma[rnd.next(52)];
    } else if (t == 3) {
      tmp[p1] = tmp[p2];
    }
    ret += tmp;
  }
  ret = genstr(ret, n);
  assert(ret.size() == n);
  puts(ret.c_str());
}

void gen6(int n) {
  std::string ret = std::string(n, 'a');
  for (int _ = 0; _ < 10; ++ _) {
    int p = rnd.next(1, n / 2);
    ret[p] = sigma[rnd.next(52)];
  }
  puts(ret.c_str());
}

void gen_antihash(int n) {
  int delta = rnd.next(51);
  for (int i = 0; i < n; ++i) {
    putchar(sigma[__builtin_popcount(i) % 2 + delta]);
  }
  puts("");
}

int main(int argc, char **argv) {
  registerGen(argc, argv, 0);
  for (int i = 0; i < 52; ++ i) {
    sigma[i] = (i < 26) ? 'a' + i : 'A' + i - 26;
  }
  assert(argc >= 4);
  int type = std::atoi(argv[1]);
  int min_n = std::atoi(argv[2]);
  int max_n = std::atoi(argv[3]);
  int N = 1000000;
  std::vector<int> ns;
  while (N >= min_n) {
    int n = rnd.next(min_n, std::min(max_n, N));
    ns.push_back(n);
    N -= n;
  }
  printf("%d\n", (int)ns.size());
  for (auto &&n: ns) {
    int t = type;
    if (t == 0) rnd.next(1, 7);
    if (t == 1) gen1(n);
    else if (t == 2) gen2(n);
    else if (t == 3) gen3(n);
    else if (t == 4) gen4(n);
    else if (t == 5) gen5(n);
    else if (t == 6) gen6(n);
    else gen_antihash(n);
  }
  return 0;
}
