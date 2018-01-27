#include <cstdio>
#include <cstring>
#include <algorithm>

const int N = 2000000 + 10;

using int64 = long long;

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

int64 S1[N], S2[N], nows;
int Count[N], t_rank[N][2], t_sa[N];
int Rank[N], sa[N], height[N];
int mx[N][22], Log2[N];

void construct(char* string, int n, int m) {
  //memset(Count, 0, sizeof(Count));
  for (int i = 0; i <= m; ++ i) Count[i] = 0;
  for (int i = 0; i < n; ++ i) Count[(int)string[i]] ++;
  for (int i = 0; i < m; ++ i) Count[i + 1] += Count[i];
  for (int i = 0; i < n; ++ i) Rank[i] = Count[(int)string[i]] - 1;
  for (int len = 1; len < n; len <<= 1) {
    for (int i = 0; i < n; ++ i) { 
      t_rank[i][0] = Rank[i];
      t_rank[i][1] = i + len < n ? Rank[i + len] + 1 : 0;
    }
    for (int i = 0; i <= n; ++ i) Count[i] = 0;
    for (int i = 0; i < n; ++ i) Count[t_rank[i][1]] ++;
    for (int i = 0; i < n; ++ i) Count[i + 1] += Count[i];
    for (int i = n - 1; i >= 0; -- i) t_sa[-- Count[t_rank[i][1]]] = i;
    for (int i = 0; i <= n; ++ i) Count[i] = 0;
    for (int i = 0; i < n; ++ i) Count[t_rank[i][0]] ++;
    for (int i = 0; i < n; ++ i) Count[i + 1] += Count[i];
    for (int i = n - 1; i >= 0; -- i) sa[-- Count[t_rank[t_sa[i]][0]]] = t_sa[i];
    Rank[sa[0]] = 0;
    for (int i = 0; i + 1 < n; ++ i) {
      Rank[sa[i + 1]] = Rank[sa[i]] + (t_rank[sa[i]][0] != t_rank[sa[i + 1]][0] || t_rank[sa[i]][1] != t_rank[sa[i + 1]][1]);
    }
  }
}

void get_height(char* string, int n) {
  for (int i = 0, len = 0; i < n; ++ i) {
    if (!Rank[i]) continue;
    int j = sa[Rank[i] - 1];
    while (i + len < n && j + len < n && string[i + len] == string[j + len]) len++;
    height[Rank[i]] = len;
    if (len) len--;
  }
}

void rmq_init(int n) {
  for (int i = 0; i < n; ++ i) mx[i][0] = height[i];
  for (int j = 1; (1 << j) < n; ++ j) {
    for (int i = 0; i + (1 << j) <= n; ++ i)
      mx[i][j] = std::min(mx[i][j - 1], mx[i + (1 << (j - 1))][j - 1]);
  }
  Log2[0] = -1;
  for (int i = 1; i < n; ++ i) Log2[i] = Log2[i >> 1] + 1;
}

inline int rmq(int a, int b) {
  int k = Log2[b - a + 1];
  return std::min(mx[a][k], mx[b - (1 << k) + 1][k]);
}

inline int lcp(int a, int b) {
  if (a < 1 || b > n) return 0;
  -- b; a = 2 * n + 1 - a;
  a = Rank[a], b = Rank[b];
  if (a == b) return 2 * n + 1 - a + 1;
  if (a > b) std::swap(a, b);
  return rmq(a + 1, b);
}

inline int bit(char c) {
  if (c >= 'a' && c <= 'z') return c - 'a';
  else if (c >= 'A' && c <= 'Z') return c - 'A' + 26;
  return -1;
}

int solve1(int i, int j) {
  if (i < 1 || j > n) return 0;
  int left = 0, right = lcp(i - 1, j + 1);
  while (left < right) {
    int mid = (left + right + 1) >> 1;
    int64 state = S1[i - mid - 1] | S2[j + mid + 1] | nows;
    bool flag = false;
    if ((state >> bit(s[i])) & 1) flag = true;
    if ((state >> bit(s[j])) & 1) flag = true;
    if (flag) left = mid;
    else right = mid - 1;
  }
  int64 state = S1[i - left - 1] | S2[j + left + 1] | nows;
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
    Log2[i] = i ? Log2[i >> 1] + 1 : -1;
  }
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    manacher(s + 1, u, n);
    s[0] = s[n + 1] = '0';
    for (int i = 1; i <= n; ++i) {
      s[n + 1 + i] = s[n - i + 1];
    }
    construct(s + 1, 2 * n + 1, 256);
    get_height(s + 1, 2 * n + 1);
    rmq_init(2 * n + 1);
    S1[0] = 0;
    for (int i = 1; i <= n; ++i) {
      S1[i] = S1[i - 1] | (1ll << bit(s[i]));
    }
    S2[n + 1] = 0;
    for (int i = n; i >= 1; --i) {
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
