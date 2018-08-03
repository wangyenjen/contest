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

const int MAX_N = 1000 + 7;
const ll MOD = 1000000000 + 7;

struct Matrix {
  ll a[2][2];

  Matrix(ll v = 0) {
    MS(a, 0);
    a[0][0] = a[1][1] = v;
  }

  ll& operator () (const int x, const int y) {
    return a[x][y];
  }
};

Matrix operator * (Matrix a, Matrix b) {
  Matrix c;
  REP(k, 2) REP(i, 2) REP(j, 2) (c(i, j) += a(i, k) * b(k, j)) %= MOD;
  return c;
}

Matrix power(Matrix a, ll n) {
  Matrix x(1);
  while (n) {
    if (n & 1) x = x * a;
    a = a * a;
    n >>= 1;
  }
  return x;
}

ll power(ll a, ll n) {
  ll x = 1;
  while (n) {
    if (n & 1) x = x * a % MOD;
    a = a * a % MOD;
    n >>= 1;
  }
  return x;
}

char S[MAX_N][MAX_N];

int main() {
  int H, W;
  ll K;
  RI(H, W, K);
  if (K <= 1) {
    PL(1);
    return 0;
  }
  REP1(i, 1, H) SR(S[i] + 1);
  int cnt = 0;
  pii c1 = MP(0, 0), c2 = MP(0, 0);
  REP1(i, 1, H) REP1(j, 1, W) cnt += S[i][j] == '#';
  REP1(i, 1, H) c1.F += (S[i][1] == '#' && S[i][W] == '#');
  REP1(i, 1, W) c2.F += (S[1][i] == '#' && S[H][i] == '#');
  REP1(i, 1, H) {
    REP1(j, 1, W) {
      if (S[i][j] == '#') {
        if (j + 1 <= W) c1.S += (S[i][j] == S[i][j + 1]);
        if (i + 1 <= H) c2.S += (S[i][j] == S[i + 1][j]);
      }
    }
  }
  if (c1.F && c2.F) {
    PL(1);
    return 0;
  }
  if (!c1.F && !c2.F) {
    PL(power(cnt, K - 1));
    return 0;
  }
  if (!c1.F) swap(c1, c2);
  Matrix a;
  a(0, 0) = cnt,  a(0, 1) = 0;
  a(1, 0) = c1.S, a(1, 1) = c1.F;
  a = power(a, K - 1);
  PL((a(0, 0) - a(1, 0) + MOD) % MOD);
  return 0;
}
