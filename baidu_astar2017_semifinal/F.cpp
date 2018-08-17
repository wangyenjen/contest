/// Author: Wang, Yen-Jen
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX_K = 15;
const int MAX_N = 30 + 1;

int G[MAX_N][MAX_N];
bool is_high[MAX_N];
int dp[MAX_N][1<<MAX_K];

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int N, M, K;
    scanf("%d%d%d", &N, &M, &K);
    memset(G, 0, sizeof(G));
    memset(is_high, 0, sizeof(is_high));
    for (int i = 0; i < M; i++) {
      int u, v;
      scanf("%d%d", &u, &v);
      G[u][v] = 1;
      G[v][u] = 1;
    }
    vector<int> H;
    for (int i = 0; i < K; i++) {
      int x;
      scanf("%d", &x);
      H.push_back(x);
      is_high[x] = 1;
    }
    vector<int> L;
    for (int i = 1; i <= N; i++) {
      if (!is_high[i]) L.push_back(i);
    }
    memset(dp, -1, sizeof(dp));
    dp[0][0] = 0;
    int ans = 0;
    for (int i = 0; i < (int)L.size(); i++) {
      for (int s = 0; s < (1 << K); s++) {
        if (dp[i][s] == -1) continue;
        dp[i + 1][s] = max(dp[i + 1][s], dp[i][s]);
        for (int a = 0; a < K; a++) {
          if (s & (1 << a)) continue;
          if (!G[L[i]][H[a]]) continue;
          for (int b = a + 1; b < K; b++) {
            if (s & (1 << b)) continue;
            if (!G[L[i]][H[b]]) continue;
            dp[i + 1][s | (1 << a) | (1 << b)] = max(dp[i + 1][s | (1 << a) | (1 << b)], dp[i][s] + 1);
            ans = max(ans, dp[i + 1][s | (1 << a) | (1 << b)]);
          }
        }
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}
