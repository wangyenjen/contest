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

const int MAX_N = 50000 + 7;

int N, L;
int vx[MAX_N], vy[MAX_N];
int tx[MAX_N], ty[MAX_N];
bool used_x[MAX_N], used_y[MAX_N];

pii find_collision() {
  double lb = -1e10, rb = 1e10;
  pii res = MP(-1, -1);
  REP(times, 50) {
    double mid = (lb + rb) / 2;
    vector<double> px, py;
    double mx_a = -1e10, mn_b = 1e10;
    REP1(i, 1, N) {
      if (!used_x[i] && tx[i] <= mid) {
        double loc = (mid - tx[i]) * vx[i];
        if (mx_a < loc) tie(mx_a, res.F) = tie(loc, i);
      }
      if (!used_y[i] && ty[i] <= mid) {
        double loc = L - (mid - ty[i]) * vy[i];
        if (mn_b > loc) tie(mn_b, res.S) = tie(loc, i);
      }
    }
    if (mx_a > mn_b) rb = mid;
    else lb = mid;
  }
  return res;
}

int main() {
  int K;
  RI(N, L, K);
  REP1(i, 1, N) RI(tx[i], vx[i]);
  REP1(i, 1, N) RI(ty[i], vy[i]);
  while (K--) {
    pii p = find_collision();
    PL(p.F, p.S);
    used_x[p.F] = 1, used_y[p.S] = 1;
  }
  return 0;
}
