#include <cmath>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <algorithm>

using uint64 = unsigned long long;
using uint32 = unsigned int;

constexpr uint32 N = 7e5;

uint64 e[N], g[N], sigma[N];
uint32 ps[N], pcnt;

uint64 lcnt[N], scnt[N];
uint64 fval[N], fsum[N];
int fsq[N];

uint64 solve(uint64 n, uint64 m) {
  const uint32 sn = sqrt(n);
  auto sieve = [sn, m] () {
    sigma[1] = 1, pcnt = 0;
    memset(ps + 1, 0, sizeof(*ps) * sn);
    for (uint32 i = 2; i <= sn; ++i) {
      if (!ps[i]) {
        ps[pcnt++] = i;
        sigma[i] = e[i] = m + 1;
        g[i] = 1;
      }
      for (uint64 j = 0, u = sn / i; j < pcnt && ps[j] <= u; ++j) {
        uint64 p = ps[j], v = i * p;
        ps[v] = 1;
        if (i % p == 0) {
          g[v] = g[i], e[v] = e[i] + m;
          sigma[v] = g[v] * e[v];
        } else {
          g[v] = sigma[i], e[v] = m + 1;
          sigma[v] = g[v] * e[v];
        }
      }
    }
  };
  auto calc_g = [sn] (uint64 n, uint64 m) {
    for (uint32 i = 1; i <= sn; ++i) {
      lcnt[i] = n / i - 1;
      scnt[i] = i - 1;
    }
    for (uint32 p = 2; p <= sn; ++p) {
      if (scnt[p] == scnt[p - 1]) continue;
      uint64 pcnt = scnt[p - 1];
      uint64 q = (uint64)p * p;
      uint32 ed = std::min<uint64>(sn, n / q);
      for (uint32 i = 1; i <= ed; ++i) {
        uint64 d = (uint64)i * p;
        if (d <= sn) lcnt[i] -= lcnt[d] - pcnt;
        else lcnt[i] -= scnt[n / d] - pcnt;
      }
      for (uint32 i = sn; i >= q; --i) scnt[i] -= scnt[i / p] - pcnt;
    }
    for (uint32 i = 1; i <= sn; ++i) {
      lcnt[i] = (lcnt[i] - scnt[sn]) * (m + 1);
      scnt[i] *= m + 1;
    }
  };
  auto calc_f = [sn] (uint64 n, uint64 m) {
    for (uint32 i = 1; i <= sn; ++i) {
      fval[i - 1] = i;
      fval[sn - i + sn] = n / i;
      fsum[i - 1] = 1;
      fsum[sn - i + sn] = 1;
    }
    for (uint32 i = 0, j = 0; i < sn * 2; ++i) {
      while (j < pcnt && (uint64)ps[j] * ps[j] <= fval[i]) ++j;
      fsq[i] = j - 1;
    }
    for (int i = pcnt - 1, bound = sn * 2 - 1; i >= 0; --i) {
      while (bound >= 0 && fsq[bound] >= i) --bound;
      uint64 p = ps[i];
      for (int j = sn * 2 - 1; j > bound; --j) {
        uint64 x = fval[j], pe = p;
        for (int c = 1; pe <= x; ++c, pe *= p) {
          uint64 y = x / pe;
          int k = y <= sn ? y - 1 : 2 * sn - n / y;
          int l = ps[std::max<int>(i, fsq[k])], r = std::min<uint64>(y, sn);
          fsum[j] += (fsum[k] + (l < r ? scnt[r] - scnt[l] : 0)) * (m * c + 1);
        }
      }
    }
    return fsum[sn * 2 - 1];
  };
  sieve();
  calc_g(n, m);
  uint64 ret = calc_f(n, m);
  for (uint32 i = 1; i <= sn; ++i) {
    ret += sigma[i] * lcnt[i];
  }
  return ret;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    uint64 n, m;
    scanf("%llu%llu", &n, &m);
    printf("%llu\n", solve(n, m));
  }
  return 0;
}
