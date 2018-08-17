/// Author: Wang, Yen-Jen
#include <cstdio>

typedef long long ll;

const int MAX_N = 10000 + 7;
const ll MOD = 1000000000 + 7;

ll dp1[MAX_N], dp2[MAX_N];

int main() {
  dp1[1] = 1;
  for (int i = 2; i < MAX_N; i++) dp1[i] = dp1[i - 1] * 2 % MOD;
  dp2[1] = 1;
  dp2[2] = 6;
  for (int i = 3; i < MAX_N; i++) dp2[i] = (dp1[i] + dp2[i - 1] * 2 + dp2[i - 2] * 4) % MOD;
  int T;
  scanf("%d", &T);
  while (T--) {
    int N;
    scanf("%d", &N);
    if (N == 1)  {
      puts("2");
      continue;
    }
    ll ans = 4 * dp2[N];
    for (int i = 2; i < N; i++) {
      ans += 2 * (4 * dp1[i - 1] * dp2[N - i] % MOD + 4 * dp1[N - i] * dp2[i - 1] % MOD);
      ans %= MOD;
    }
    printf("%lld\n", ans);
  }
  return 0;
}
