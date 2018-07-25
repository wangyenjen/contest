// Author: Yen-Jen Wang
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 100000000 + 7;
const int MAX_N = 10000000 + 7;

ll power[MAX_N];

int main() {
  power[0] = 1;
  for (int i = 1; i < MAX_N; i++)
    power[i] = power[i - 1] * 2 % MOD;
  int N;
  while (scanf("%d", &N) != EOF && N) {
    ll ans = 0;
    if (N >= 1) (ans += 1ll * N * power[N - 1]) %= MOD;
    if (N >= 2) (ans += 1ll * N * (N - 1) % MOD * 7 * power[N - 2]) %= MOD;
    if (N >= 3) (ans += 1ll * N * (N - 1) % MOD * (N - 2) % MOD * 6 * power[N - 3]) %= MOD;
    if (N >= 4) (ans += 1ll * N * (N - 1) % MOD * (N - 2) % MOD * (N - 3) % MOD * power[N - 4]) %= MOD;
    printf("%lld\n", ans);
  }
  return 0;
}
