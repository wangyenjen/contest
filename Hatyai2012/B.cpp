/// Author: Wang, Yen-Jen
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int HF = 180000;

int main() {
  int N;
  for (int kcase = 1; ; kcase++) {
    scanf("%d%*d", &N);
    if (N == 0) break;
    vector<int> vs;
    for (int i = 0; i < N; i++) {
      int x, y;
      scanf("%d.%d", &x, &y);
      vs.push_back(x * 1000 + y);
    }
    sort(vs.begin(), vs.end());
    for (int i = 0; i < N; i++) vs.push_back(vs[i] + 2 * HF);
    ll ans = 1ll * N * (N - 1) * (N - 2) / 6;
    for (int i = 0, j = 0; i < N; i++) {
      while (vs[j + 1] <= vs[i] + HF) j++;
      int c = j - i;
      ans -= 1ll * c * (c - 1) / 2;
    }
    printf("Case %d: %lld\n", kcase, ans);
  }
  return 0;
}
