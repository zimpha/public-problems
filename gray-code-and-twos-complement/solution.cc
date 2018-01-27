#include <cstdio>
#include <cstring>
#include <cassert>

constexpr int N = 1e6 + 10, mod = 1e9 + 7;

char C[N], G[N];
bool canSet[N];
int dp[N][2][2][2], n;

bool add(int &a, int b) {
  if (b != -1) {
    if (a == -1) a = b;
    else a += b;
    if (a >= mod) a -= mod;
    return true;
  }
  return false;
}

void calc(int i) {
  if (C[i] != '1') { // set C[i] to 0
    if (C[i - 1] != '1' && G[i] != '1') { // C[i-1] = 0, G[i] = 0
      add(dp[i][0][0][0], dp[i - 1][0][0][0]);
    }
    if (C[i - 1] != '0' && G[i] != '0') { // C[i-1] = 1, G[i] = 1
      add(dp[i][0][0][0], dp[i - 1][1][0][0]);
    }
    if (C[i - 1] != '1' && G[i] != '1') { // C[i-1] = 0, G[i] = 0
      add(dp[i][0][1][0], dp[i - 1][0][1][0]);
    }
    if (C[i - 1] != '0' && G[i] != '0') { // C[i-1] = 1, G[i] = 1
      add(dp[i][0][1][0], dp[i - 1][1][1][1]);
    }
  }
  if (C[i] != '0') { // set C[i] to 1
    if (C[i - 1] != '1' && G[i] != '0') { // C[i-1] = 0, G[i] = 1
      add(dp[i][1][0][0], dp[i - 1][0][0][0]);
    }
    if (C[i - 1] != '0' && G[i] != '1') { // C[i-1] = 1, G[i] = 0
      add(dp[i][1][0][0], dp[i - 1][1][0][0]);
    }
  }
  if (C[i] != '0' && canSet[i]) { // set i to k
    if (C[i - 1] != '1' && G[i] != '1') { // C[i-1] = 0, G[i] = 1
      add(dp[i][1][1][1], dp[i - 1][0][0][0]);
    }
    if (C[i - 1] != '0' && G[i] != '0') { // C[i-1] = 1, G[i] = 0
      add(dp[i][1][1][1], dp[i - 1][1][0][0]);
    }
  }
}

bool checkAllZero() {
  for (int i = 0; i < n; ++ i) {
    if (C[i] == '1') return false;
  }
  for (int i = 0; i < n; ++ i) {
    if (G[i] == '1') return false;
  }
  return true;
}

void restore(int i, int a, int b, int c) {
  C[i] = a + '0';
  if (i == 0) return;
  int tmp = a * 4 + b * 2 + c;
  if (tmp == 0) { // 0 0 0
    if (dp[i - 1][0][0][0] == 1 && G[i] != '1') restore(i - 1, 0, 0, 0);
    if (dp[i - 1][1][0][0] == 1 && G[i] != '0') restore(i - 1, 1, 0, 0);
  }
  else if (tmp == 2) { // 0 1 0
    if (dp[i - 1][0][1][0] == 1 && G[i] != '1') restore(i - 1, 0, 1, 0);
    if (dp[i - 1][1][1][1] == 1 && G[i] != '0') restore(i - 1, 1, 1, 1);
  }
  else if (tmp == 4) { // 1 0 0
    if (dp[i - 1][0][0][0] == 1 && G[i] != '0') restore(i - 1, 0, 0, 0);
    if (dp[i - 1][1][0][0] == 1 && G[i] != '1') restore(i - 1, 1, 0, 0);
  }
  else if (tmp == 7) { // 1 1 1
    if (dp[i - 1][0][0][0] == 1 && G[i] != '1') restore(i - 1, 0, 0, 0);
    if (dp[i - 1][1][0][0] == 1 && G[i] != '0') restore(i - 1, 1, 0, 0);
  }
}

void output() {
  int ret = -1;
  bool flag = checkAllZero();
  add(ret, dp[n - 1][0][1][0]);
  add(ret, dp[n - 1][1][1][1]);
  if (ret == -1) {
    if (flag) {
      puts("UNIQUE");
      for (int i = 0; i < n; ++ i) putchar('0');
      puts("");
      for (int i = 0; i < n; ++ i) putchar('0');
      puts("");
    }
    else {
      puts("IMPOSSIBLE");
    }
  }
  else {
    ret = (ret + flag) % mod;
    if (ret == 1) {
      puts("UNIQUE");
      if (dp[n - 1][0][1][0] == 1) restore(n - 1, 0, 1, 0);
      if (dp[n - 1][1][1][1] == 1) restore(n - 1, 1, 1, 1);
      int k = n - 1;
      while (k >= 0 && C[k] == '0') G[k] = '0', -- k;
      if (k == 0) {
        G[0] = '1';
        G[1] = '1';
      }
      else {
        G[0] = '0' + !(C[0] - '0');
        for (int i = 1; i < k; ++ i) {
          int a = C[i - 1] - '0', b = C[i] - '0';
          G[i] = '0' + (a ^ b);
        }
        G[k] = C[k - 1];
        if (k + 1 < n) G[k + 1] = '1';
      }
      puts(G);
      puts(C);
    }
    else {
      printf("AMBIGUOUS %d\n", ret);
    }
  }
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%s%s", G, C);
    n = strlen(C);
    for (int i = 0; i < n; ++ i) {
      memset(dp[i], -1, sizeof(dp[i]));
      canSet[i] = 0;
    }
    // find all the position can set to k
    for (int i = n - 1, cnt = 0; i >= 0; -- i) {
      if (C[i] == '?' || C[i] == '1') {
        canSet[i] = (cnt == n - 1 - i);
      }
      if (C[i] == '?' || C[i] == '0') ++ cnt;
    }
    // deal with first digit
    if (C[0] != '1') {
      if (G[0] != '0') dp[0][0][0][0] = 1;
    }
    if (C[0] != '0') {
      if (G[0] != '1') dp[0][1][0][0] = 1;
      if (G[0] != '0' && canSet[0]) dp[0][1][1][1] = 1;
    }
    for (int i = 1; i < n; ++ i) calc(i);
    output();
  }
  return 0;
}
