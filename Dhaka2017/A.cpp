// Author: Yen-Jen Wang
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
  while (1) {
    int x1, y1, x2, y2;
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    if (x1 == 0 && y1 == 0 && x2 == 0 && y2 == 0) break;
    if (x1 > x2) {
      swap(x1, x2);
      swap(y1, y2);
    }
    ll d = x2 - x1 - (x1 % 2 == y1 % 2);
    ll ans = x2 - x1;
    if (abs(y2 - y1) >= d) ans += abs(y2 - y1);
    else if (abs(y2 - y1) % 2 == d % 2) ans += d;
    else ans += d + 1;
    printf("%lld\n", ans);
  }
  return 0;
}
