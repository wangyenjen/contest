// Author: Yen-Jen Wang
#include <bits/stdc++.h>

using namespace std;

bool isLeapYear(int year) {
  if (year % 400 == 0) return 1;
  else if (year % 100 == 0) return 0;
  else if (year % 4 == 0) return 1;
  else return 0;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int kcase = 1; kcase <= T; kcase++) {
    int D, M, Y, QY;
    scanf("%d%d%d%d", &D, &M, &Y, &QY);
    int ans = 0;
    if (QY > Y) {
      for (int i = Y + 1; i <= QY; i++) {
        if (D == 29 && M == 2) ans += isLeapYear(i);
        else ans++;
      }
    }
    printf("Case %d: %d\n", kcase, ans);
  }
  return 0;
}
