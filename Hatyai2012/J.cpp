/// Author: Wang, Yen-Jen
#include <bits/stdc++.h>

using namespace std;

bool check(char c) {
  if ('a' <= c && c <= 'z') return 1;
  else if ('A' <= c && c <= 'Z') return 1;
  else return c == '-';
}

char adjust(char c) {
  if ('A' <= c && c <= 'Z') return c - 'A' + 'a';
  else return c;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  string str;
  string ans = "";
  while (cin >> str) {
    int n = (int)str.size();
    string s = "";
    for (int i = 0; i <= n; i++) {
      if (i == n || !check(str[i])) {
        if ((int)s.size() > (int)ans.size()) ans = s;
        s = "";
      }
      else s += adjust(str[i]);
    }
  }
  cout << ans << '\n';
  return 0;
}
