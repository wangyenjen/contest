/// Author: Wang, Yen-Jen
#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n;
  vector<tuple<int, int, int, string> > vs;
  cin >> n;
  for (int i = 0; i < n; i++) {
    string name;
    int d, m, y;
    cin >> name >> d >> m >> y;
    vs.emplace_back(y, m, d, name);
  }
  sort(vs.begin(), vs.end());
  cout << get<3>(vs.back()) << '\n' << get<3>(vs[0]) << '\n';
  return 0;
}
