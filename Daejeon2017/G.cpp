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

const int MAX_N = 25000 + 7;

struct Node {
  int type, x, y;

  bool operator < (const Node &rhs) const {
    return x < rhs.x;
  }
};

int main() {
  int n, m, ya, yb;
  RI(n, m, ya);
  vector<Node> a, b;
  REP(i, n) {
    int x, y;
    RI(x, y);
    a.PB({0, x, y});
  }
  RI(yb);
  REP(i, m) {
    int x, y;
    RI(x, y);
    b.PB({1, x, y});
  }
  if ((a[0].y > ya) != (b[0].y > yb)) {
    PL(0, 0);
    return 0;
  }
  if (a[0].y < ya) {
    ya = -ya, yb = -yb;
    REP(i, n) a[i].y = -a[i].y, a[i].type ^= 1;
    REP(i, m) b[i].y = -b[i].y, b[i].type ^= 1;
    swap(ya, yb);
    swap(a, b);
    swap(n, m);
  }
  vector<Node> c;
  c.resize(SZ(a) + SZ(b));
  merge(ALL(a), ALL(b), c.begin());
  int last_x = -1, ans1 = 0;
  ll ans2 = 0, t = 0;
  bool can_calc = yb > ya;
  for (int i = 0; i < n + m; i++) {
    if (!c[i].type) {
      if (~last_x) {
        t += (ll)(c[i].x - last_x) * (yb - ya);
        if (c[i].y < yb) last_x = c[i].x;
        else last_x = -1, ans1++, ans2 += t, t = 0;
      }
      ya = c[i].y;
      if (ya >= yb) can_calc = 0;
    }
    else {
      if (~last_x) {
        t += (ll)(c[i].x - last_x) * (yb - ya);
        last_x = c[i].x;
      }
      yb = c[i].y;
      if (!can_calc && last_x == -1 && yb > ya) last_x = c[i].x;
    }
  }
  PL(ans1, ans2);
  return 0;
}
