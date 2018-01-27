#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>

using uint32 = unsigned int;
using uint64 = unsigned long long;
using uint128 = __uint128_t;

const int N = 7.1e6, M = 1e4;

bool mark[N + 1];
uint64 sigma[N + 1];
int mu[N + 1], f[N + 1], g[N + 1];
int ps[M], pcnt, bound;

void sieve(int n) {
  bound = n;
  mu[1] = sigma[1] = 1;
  for (int i = 2; i <= n; ++i) {
    if (!mark[i]) {
      mu[i] = -1;
      sigma[i] = i + 1;
      f[i] = i + 1;
      g[i] = 1;
      if ((uint64)i * i <= n) ps[pcnt++] = i;
    }
    for (int j = 0, u = n / i; j < pcnt && ps[j] <= u; ++j) {
      const int p = ps[j], v = p * i;
      mark[v] = 1;
      if (i % p == 0) {
        mu[v] = 0;
        g[v] = g[i];
        f[v] = f[i] * p + 1;
        sigma[v] = g[v] * f[v];
        break;
      } else {
        mu[v] = -mu[i];
        g[v] = sigma[i];
        f[v] = p + 1;
        sigma[v] = g[v] * f[v];
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    sigma[i] += sigma[i - 1];
  }
}

uint64 divsum_64(uint64 n) {
  uint64 ret = 0, prev = 0;
  for (uint64 i = 1, j; i <= n; i = j + 1) {
    const uint64 u = n / i;
    j = n / u;
    uint64 now = (uint128)j * (j + 1) / 2;
    ret += (now - prev) * u;
    prev = now;
  }
  return ret;
}

uint64 divsum_32(uint32 n) {
  if (n <= bound) return sigma[n];
  uint64 ret = 0, prev = 0;
  for (uint32 i = 1, j; i <= n; i = j + 1) {
    const uint32 u = n / i;
    j = n / u;
    uint64 now = (uint64)j * (j + 1) / 2;
    ret += (now - prev) * u;
    prev = now;
  }
  return ret;
}

int main() {
  int T;
  scanf("%d", &T);
  std::vector<uint64> tests(T);
  for (int i = 0; i < T; ++i) {
    scanf("%llu", &tests[i]);
  }
  uint64 m = *std::max_element(tests.begin(), tests.end());
  m = sqrtl(m);
  m = std::max<uint64>(m, 50000);
  sieve(m);
  for (const auto &n: tests) {
    const int sn = sqrtl(n);
    const int w = sqrtl(n / 1000000000);
    uint64 ret = 0;
    for (int i = 1; i <= w; ++i) if (mu[i]) {
      ret += (uint64)(i * mu[i]) * divsum_64(n / ((uint64)i * i));
    }
    for (int i = w + 1; i <= sn; ++i) if (mu[i]) {
      ret += (uint64)(i * mu[i]) * divsum_32(n / ((uint64)i * i));
    }
    printf("%llu\n", ret);
  }
  return 0;
}
