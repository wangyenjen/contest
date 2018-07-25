// Author: Yen-Jen Wang
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 100000 + 7;

bool can(char cl, char cr) {
  if (cl == '(' && cr == ')') return 1;
  if (cl == '{' && cr == '}') return 1;
  if (cl == '[' && cr == ']') return 1;
  if (cl == '<' && cr == '>') return 1;
  return 0;
}

int dp[MAX_N];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int T;
  cin >> T;
  for (int kcase = 1; kcase <= T; kcase++) {
    string S;
    cin >> S;
    int N = (int)S.size();
    memset(dp, 0, sizeof(int) * (N + 1));
    for (int i = N - 2; i >= 0; i--) {
      if (can(S[i], S[i + 1])) dp[i] = 2 + dp[i + 2];
      else {
        int t = dp[i + 1];
        if (can(S[i], S[i + t + 1])) dp[i] = 2 + t + dp[i + t + 2];
      }
    }
    printf("Case %d:\n", kcase);
    for (int i = 0; i < N; i++) printf("%d\n", dp[i]);
  }
  return 0;
}
