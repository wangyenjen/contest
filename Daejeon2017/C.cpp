/// Author: Wang, Yen-Jen
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 100000 + 7;

int dp[MAX_N];
int deg[MAX_N];
vector<int> G[MAX_N];

int dfs(int u) {
  if (dp[u]) return dp[u];
  dp[u] = 1;
  for (int v : G[u]) dp[u] = max(dp[u], dfs(v) + 1);
  return dp[u];
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  vector<pair<int, int> > es;
  while (m--) {
    int u, v;
    scanf("%d%d", &u, &v);
    deg[u]++;
    deg[v]++;
    es.emplace_back(u, v);
  }
  vector<pair<int, int> > vs;
  for (int i = 0; i < n; i++) vs.emplace_back(deg[i], i);
  sort(vs.begin(), vs.end());
  vector<pair<int, int> > vs2;
  for (int i = 0; i < n; i++) {
    if (!i || vs2.back().first != vs[i].first) vs2.push_back(vs[i]);
  }
  for (pair<int, int> &e : es) {
    if (deg[e.second] > deg[e.first]) G[e.first].push_back(e.second);
    if (deg[e.first] > deg[e.second]) G[e.second].push_back(e.first);
  }
  int ans = 0;
  for (int i = 0; i < n; i++) ans = max(ans, dfs(i));
  printf("%d\n", ans);
  return 0;
}
