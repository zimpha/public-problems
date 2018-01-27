#include <cstdio>
#include <cstring>
#include <algorithm>

using uint64 = unsigned long long;

const int N = 2000000 + 10;
const int seed = 257;

uint64 S1[N], S2[N], nows;
uint64 H1[N], H2[N], pp[N];
int u[N], n;
char s[N];

//传入字符串s和长度n，返回数组u[]
//u[i]表示以i/2为圆心的最长回文子串的直径
//比如字符串babbaa，看作b.a.b.b.a.a
//相应的u[]为{1, 0, 3, 0, 1, 4, 1, 0, 1, 2, 1}
void manacher(const char *s, int u[], int n) {
  for (int i = 0; i < 2 * n; ++ i) u[i] = 0;
  for (int i = 0, j = 0, k; i < 2 * n; i += k, j = std::max(j - k, 0)) {
    while (i >= j && i + j + 1 < 2 * n && s[(i - j) >> 1] == s[(i + j + 1) >> 1]) ++j;
    for (k = 1, u[i] = j; i >= k && u[i] >= k && u[i - k] != u[i] - k; ++k) {
      u[i + k] = std::min(u[i - k], u[i] - k);
    }
  }
}

inline int bit(char c) {
  if (c >= 'a' && c <= 'z') return c - 'a';
  else if (c >= 'A' && c <= 'Z') return c - 'A' + 26;
  return -1;
}

int lcp(int i, int j) {
  if (i < 1 || j > n) return 0;
  int left = 0, right = std::min(i, n - j + 1);
  while (left < right) {
    int mid = (left + right + 1) >> 1;
    uint64 hi = H1[i] - pp[mid] * H1[i - mid];
    uint64 hj = H2[j] - pp[mid] * H2[j + mid];
    if (hi == hj) left = mid;
    else right = mid - 1;
  }
  return left;
}

int solve1(int i, int j) {
  if (i < 1 || j > n) return 0;
  int left = 0, right = lcp(i - 1, j + 1);
  while (left < right) {
    int mid = (left + right + 1) >> 1;
    uint64 state = S1[i - mid - 1] | S2[j + mid + 1] | nows;
    bool flag = false;
    if ((state >> bit(s[i])) & 1) flag = true;
    if ((state >> bit(s[j])) & 1) flag = true;
    if (flag) left = mid;
    else right = mid - 1;
  }
  uint64 state = S1[i - left - 1] | S2[j + left + 1] | nows;
  bool flag = false;
  if ((state >> bit(s[i])) & 1) flag = true;
  if ((state >> bit(s[j])) & 1) flag = true;
  if (flag) return left * 2 + 2;
  else return 0;
}

inline bool check(int a, int b, int c, int d) {
  if (s[b] == s[c] && s[a] == s[d]) return true;
  if (s[a] == s[c] && s[b] == s[d]) return true;
  return false;
}

int solve2(int pi, int pj) {
  if (pi < 1 || pj > n) return 0;
  int len1 = lcp(pi - 1, pj + 1), ret = 0;
  int i = pi - len1 - 1, j = pj + len1 + 1;
  if (check(pi, pj, i, j)) {
    int len2 = lcp(i - 1, j + 1);
    ret = (len1 + len2 + 2) * 2;
  }
  return ret;
}

int gao1(int center) {
  int ret = u[center * 2 - 2], len = ret / 2;
  nows = (1ll << bit(s[center]));
  int i = center - len - 1, j = center + len + 1;
  ret += std::max(solve1(i, j), solve2(i, j));
  return ret;
}

int gao2(int center) {
  int ret = u[center * 2 - 1], len = ret / 2;
  nows = 0;
  int i = center - len, j = center + len + 1;
  ret += std::max(solve1(i, j), solve2(i, j));
  return ret;
}

int main() {
  for (int i = 0; i < N; ++ i) {
    pp[i] = i ? pp[i - 1] * seed : 1;
  }
  int T;
  scanf("%d", &T);
  for  (int cas = 1; cas <= T; ++cas) {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    manacher(s + 1, u, n);
    s[0] = s[n + 1] = 52;
    H1[0] = S1[0] = 0;
    for (int i = 1; i <= n; ++i) {
      H1[i] = H1[i - 1] * seed + s[i];
      S1[i] = S1[i - 1] | (1ll << bit(s[i]));
    }
    H2[n + 1] = S2[n + 1] = 0;
    for (int i = n; i >= 1; --i) {
      H2[i] = H2[i + 1] * seed + s[i];
      S2[i] = S2[i + 1] | (1ll << bit(s[i]));
    }
    int ret = 0;
    for (int i = 1; i <= n; ++i) {
      ret = std::max(ret, gao1(i));
      ret = std::max(ret, gao2(i));
    }
    printf("%d\n", ret);
  }
  return 0;
}
