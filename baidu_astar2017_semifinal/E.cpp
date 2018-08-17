/// Author: Wang, Yen-Jen
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

const int MAX_LEN = 100 + 7;
const ll MOD = 1000000000 + 7;

int num[MAX_LEN];
ll dp[MAX_LEN][11][2][2];

ll dfs(int n, int pre, bool state, bool flag) {
  ll &res = dp[n][pre][state][flag];
  if (res != -1) return res;
  res = 0;
  int st = 0;
  int ed = flag ? num[n] : 9;
  if (state) st = pre;
  if (st > ed) return res = 0;
  if (n == 0) return res = ed - st + 1;
  for (int i = st; i <= ed; i++) {
    if (state) res += dfs(n - 1, i, 1, flag && (i == ed));
    else {
      if (pre == 10 && i == 0) res += dfs(n - 1, 10, 0, flag && (i == ed));
      else if (i <= pre) res += dfs(n - 1, i, 0, flag && (i == ed));
      else res += dfs(n - 1, i, 1, flag && (i == ed));
    }
    if (res >= MOD) res -= MOD;
  }
  return res;
}

ll calc(const string &s) {
  int n = (int)s.size();
  for (int i = 0; i < n; i++) num[n - 1 - i] = s[i] - '0';
  memset(dp, -1, sizeof(dp));
  return dfs(n - 1, 10, 0, 1);
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    string s;
    cin >> s;
    ll ans = calc(s) - 1;
    if (ans < 0) ans += MOD;
    cout << ans << '\n';
  }
  return 0;
}
