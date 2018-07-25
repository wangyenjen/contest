// Author: Yen-Jen Wang
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
  int T;
  scanf("%d", &T);
  for (int kcase = 1; kcase <= T; kcase++) {
    int E, P, K, R;
    scanf("%d%d%d%d", &E, &P, &K, &R);
    ll ans = -1;
    if (E <= P * K) ans = E / P + (E % P != 0);
    else {
      ll q = E - R;
      ll p = 1ll * P * K - R;
      if (p > 0) {
        ll t = q / p + (q % p != 0);
        ll t2 = E + (R * (t - 1));
        ans = t2 / P + (t2 % P != 0);
      }
    }
    printf("Case %d: %lld\n", kcase, ans);
  }
  return 0;
}
