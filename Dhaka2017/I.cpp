// Author: Yen-Jen Wang
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 5000000 + 7;
const ll MOD = 100000000 + 7;

bool vis[MAX_N];
vector<int> prime;

int main() {
  for (int i = 2; i < MAX_N; i++) {
    if (vis[i]) continue;
    prime.push_back(i);
    for (int j = i + i; j < MAX_N; j += i) vis[j] = 1;
  }
  int N;
  while (scanf("%d", &N) != EOF && N) {
    ll ans = 1;
    for (int p : prime) {
      if (p > N) break;
      ll d = p;
      ll s = 0;
      while (d <= N) {
        ll x = N / d;
        s = (s + (N % d + 1) * x % MOD + x * (x - 1) / 2 % MOD * d) % MOD;
        d *= p;
      }
      ans = ans * (s + 1) % MOD;
    }
    printf("%lld\n", ans);
  }
  return 0;
}
