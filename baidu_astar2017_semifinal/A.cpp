/// Author: Wang, Yen-Jen
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

const ll MOD = 1000000000 + 7;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    string s;
    cin >> s;
    int state = 0;
    string t = "", t2 = "";
    for (char c : s) {
      if (state == 0) {
        if (c == '(') state = 1;
        else t = t + c;
      }
      else if (state == 1) {
        if (c == ')') state = 2;
        else t2 = t2 + c;
      }
      else if (state == 2) {
        if (c == '#') state = 3;
        else t = t + t2, t2 = "", state = 0;
      }
      else if (state == 3) {
        if (c == '(') continue;
        else if (c == ')') state = 0, t2 = "";
        else {
          for (int i = 0; i < c - '0'; i++) t = t + t2;
        }
      }
    }
    ll res = 0;
    for (char c : t) res = (res * 10 + (c - '0')) % MOD;
    cout << res << '\n';
  }
  return 0;
}
