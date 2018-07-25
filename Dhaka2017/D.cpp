// Author: Yen-Jen Wang
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1000 + 7;
const int MAX_K = 100 + 7;

int N, K;
int dp[MAX_N][MAX_K];
vector<int> G[MAX_N];

void dfs(int u, int fa = 0) {
  int cnt = 0;
  dp[u][0] = 1;
  dp[u][K] = 1;
  for (int v : G[u]) {
    if (v == fa)
      continue;
    cnt++;
    dfs(v, u);
    for (int i = K; i >= 1; i--) {
      if (dp[u][i - 1] != -1 && dp[v][K] != -1)
        dp[u][i] = max(dp[u][i], dp[u][i - 1] + dp[v][K]);
    }
  }
}

int main() {
  int T;
  scanf("%d", &T);
  for (int kcase = 1; kcase <= T; kcase++) {
    scanf("%d%d", &N, &K);
    for (int i = 1; i <= N; i++) {
      G[i].clear();
      memset(dp[i], -1, sizeof(int) * (K + 1));
    }
    for (int i = 1; i < N; i++) {
      int u, v;
      scanf("%d%d", &u, &v);
      G[u].push_back(v);
      G[v].push_back(u);
    }
    dfs(1);
    printf("Case %d: %d\n", kcase, dp[1][K]);
  }
  return 0;
}
