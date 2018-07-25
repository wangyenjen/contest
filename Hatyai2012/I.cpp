/// Author: Wang, Yen-Jen
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 100000 + 1;

bool vis[MAX_N];

int main() {
  vis[0] = 1;
  vis[1] = 1;
  for (int i = 2; i < MAX_N; i++) {
    if (!vis[i]) {
      for (int j = i + i; j < MAX_N; j += i) vis[j] = 1;
    }
  }
  ios::sync_with_stdio(0);
  cin.tie(0);
  string s;
  while (cin >> s, s != "0") {
    int n = (int)s.size();
    int ans = 0;
    for (int i = 0; i < n; i++) {
      int t = 0;
      for (int j = 0; j < 5 && t < MAX_N && i + j < n; j++) {
        t = t * 10 + (s[i + j] - '0');
        if (t < MAX_N && !vis[t]) ans = max(ans, t);
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}
