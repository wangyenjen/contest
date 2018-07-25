// Author: Yen-Jen Wang
#include <bits/stdc++.h>

using namespace std;

int main() {
  int N;
  while (scanf("%d",  &N) != EOF && N) {
    map<int, int> tag;
    for (int i = 0; i < N; i++) {
      int x, y;
      scanf("%d%d", &x, &y);
      int lb = x - y;
      int rb = x + y;
      tag[lb]++;
      tag[rb + 1]--;
    }
    int s = 0, ans = 0;
    for (auto it: tag) {
      s += it.second;
      ans = max(ans, s);
    }
    printf("%d\n", ans);
  }
  return 0;
}
