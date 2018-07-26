/// {{{ Author: Wang, Yen-Jen
// include
#include <bits/stdc++.h>

// using
using namespace std;

// types
typedef long long ll;
typedef pair<int,int> pii;

// macro
#define SZ(x) ((int)x.size())
#define ALL(x) (x).begin() , (x).end()
#define REP(i , n) for(int i = 0; i < int(n); i++)
#define REP1(i , a , b) for(int i = a; i <= int(b); i++)
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define LC o<<1 , l , m
#define RC o<<1|1 , m + 1 , r
#define MS(x , v) memset(x , (v) , sizeof(x))

// input
inline bool SR(int &x) {
  return scanf("%d",&x) == 1;
}

inline bool SR(ll &x) {
  return scanf("%lld",&x) == 1;
}

inline bool SR(double &x) {
  return scanf("%lf",&x) == 1;
}

inline bool SR(char *s) {
  return scanf("%s",s) == 1;
}

inline bool RI() {
  return true;
}

template<typename I , typename... T> inline bool RI(I &x , T&... tail) {
  return SR(x) && RI(tail...);
}

// output
inline void SP(const int x) {
  printf("%d",x);
}

inline void SP(const ll x) {
  printf("%lld",x);
}

inline void SP(const double x) {
  printf("%.16lf",x);
}

inline void SP(const char *s) {
  printf("%s",s);
}

inline void PL() {
  puts("");
}

template<typename I , typename... T> inline void PL(const I x , const T... tail) {
  SP(x);
  if(sizeof...(tail)) putchar(' ');
  PL(tail...);
}

// debug
#define WangYenJen

#ifdef WangYenJen
template<typename I> void _DOING(const char *s , I&& x) {
  cerr << s << " = " << x << endl;
}

template<typename I , typename... T> void _DOING(const char *s , I&& x , T&&... tail) {
  int c = 0;
  while(*s != ',' || c != 0) {
    if(*s == '(' || *s == '[' || *s == '{') c++;
    if(*s == ')' || *s == ']' || *s == '}') c--;
    cerr << *s++;
  }
  cerr << " = " << x << " , ";
  _DOING(s + 1 , tail...);
}

#define DEBUG(...) \
do {\
  fprintf(stderr , "%s: Line %d - ",__PRETTY_FUNCTION__,__LINE__);\
  _DOING(#__VA_ARGS__ , __VA_ARGS__);\
} while(0);

#else
#define DEBUG(...)

#endif

// constant number
const int INF = 0x3f3f3f3f;
const ll INF64 = 0x3f3f3f3f3f3f3f3fll;

// random function
inline int RAND() {
  static int x = 880301;
  return (x = x * 0xdefaced + 1) % 0x7fffffff;
}
/// }}}

const int MAX_N = 300 + 7;

int n;
int cnt[MAX_N];
vector<int> ans;
vector<int> G[MAX_N];
vector<vector<int> > vv;

bool check(int id, int p1) {
  ans.clear();
  REP(i, p1) ans.PB(vv[id][i] + 1);
  ans.PB(1);
  REP1(i, p1, n - 2) ans.PB(vv[id][i] + 1);
  vector<vector<int> > vv2;
  REP1(i, 1, n) {
    vector<int> v;
    REP(j, n) {
      if (ans[j] < i) v.PB(ans[j]);
      else if (ans[j] > i) v.PB(ans[j] - 1);
    }
    vv2.PB(v);
  }
  sort(vv2.begin(), vv2.end());
  bool res = (vv2 == vv);
  vv2.clear();
  vv2.shrink_to_fit();
  return res;
}

int main() {
  freopen("permutation.in", "r", stdin);
  freopen("permutation.out", "w", stdout);
  RI(n);
  REP1(i, 1, n) {
    vector<int> v;
    REP(i, n - 1) {
      int x;
      RI(x);
      v.PB(x);
      if (x == 1) cnt[i]++;
    }
    vv.PB(v);
  }
  sort(vv.begin(), vv.end());
  int p = -1;
  REP(i, n - 1) {
    if (p == -1 || cnt[i] > cnt[p]) p = i;
  }
  REP(i, n) {
    bool flag = 0;
    REP1(j, -1, 1) {
      int p1 = p + j;
      if (p1 < 0 || p1 >= n) continue;
      if (check(i, p1)) {
        flag = 1;
        break;
      }
    }
    if (flag) break;
  }
  REP(i, n) printf("%d%c", ans[i], " \n"[i == n - 1]);
  return 0;
}
