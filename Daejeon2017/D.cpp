/// Author: Wang, Yen-Jen
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1000 + 7;

bool dp[MAX_N];
bool vis[MAX_N];

bool dfs(int x) {
  if (x == 1) return 1;
  if (vis[x]) return 0;
  vis[x] = 1;
  int s = 0;
  int y = x;
  while (y) {
    s += (y % 10) * (y % 10);
    y /= 10;
  }
  if (dfs(s)) {
    vis[x] = 0;
    return 1;
  }
  vis[x] = 0;
  return 0;
}

bool dfs2(int x) {
  if (x <= 1000) return dp[x];
  int s = 0;
  int y = x;
  while (y) {
    s += (y % 10) * (y % 10);
    y /= 10;
  }
  return dfs2(s);
}

int main() {
  for (int i = 1; i <= 1000; i++) dp[i] = dfs(i);
  int n;
  scanf("%d", &n);
  puts(dfs2(n) ? "HAPPY" : "UNHAPPY");
  return 0;
}
