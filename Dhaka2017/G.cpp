// Author: Yen-Jen Wang
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 100000 + 7;

void fwt(ll a[], int n, bool inv = 0) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < (1<<n); j++) {
      if (j & (1<<i)) {
        ll t = a[j];
        a[j] = a[j ^ (1<<i)] - t;
        a[j ^ (1<<i)] += t;
      }
    }
  }
  if (inv) {
    n = 1<<n;
    for (int i = 0; i < n; i++) a[i] /= n;
  }
}

ll cnt[1<<16];
vector<pair<int, int> > G[MAX_N];

void dfs(int u, int fa = 0, int pre_xor = 0) {
  cnt[pre_xor]++;
  for (pair<int, int> p : G[u]) {
    int v, w;
    tie(v, w) = p;
    if (v != fa) dfs(v, u, pre_xor ^ w);
  }
}

int main() {
  int T;
  scanf("%d", &T);
  for (int kcase = 1; kcase <= T; kcase++) {
    int N;
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) G[i].clear();
    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i < N; i++) {
      int u, v, w;
      scanf("%d%d%d", &u, &v, &w);
      G[u].emplace_back(v, w);
      G[v].emplace_back(u, w);
    }
    dfs(1);
    fwt(cnt, 16);
    for (int i = 0; i < (1<<16); i++) cnt[i] *= cnt[i];
    fwt(cnt, 16, 1);
    cnt[0] -= N;
    for (int i = 0; i < (1<<16); i++) cnt[i] /= 2;
    printf("Case %d:\n", kcase);
    for (int i = 0; i < (1<<16); i++) printf("%lld\n", cnt[i]);
  }
  return 0;
}
