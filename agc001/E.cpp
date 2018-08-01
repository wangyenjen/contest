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

const ll MOD = 1000000000 + 7;
const int MAX_N = 200000 + 7;
const int MAX_X = 4000 + 7;
const int DELTA = 2000;

ll dp[MAX_X][MAX_X];
ll dp2[MAX_X][MAX_X];
int A[MAX_N], B[MAX_N];

ll power(ll a, ll n) {
  ll x = 1;
  while (n) {
    if (n & 1) x = x * a % MOD;
    a = a * a % MOD;
    n >>= 1;
  }
  return x;
}

ll inv(ll x) {
  return power(x, MOD - 2);
}

int main() {
  int N;
  RI(N);
  REP(i, N) {
    RI(A[i], B[i]);
    dp[-A[i] + DELTA][-B[i] + DELTA]++;
  }
  dp2[0][0] = 1;
  REP(i, MAX_X) {
    REP(j, MAX_X) {
      if (i) {
        dp[i][j] += dp[i - 1][j];
        dp2[i][j] += dp2[i - 1][j];
        if (dp[i][j] >= MOD) dp[i][j] -= MOD;
        if (dp2[i][j] >= MOD) dp2[i][j] -= MOD;
      }
      if (j) {
        dp[i][j] += dp[i][j - 1];
        dp2[i][j] += dp2[i][j - 1];
        if (dp[i][j] >= MOD) dp[i][j] -= MOD;
        if (dp2[i][j] >= MOD) dp2[i][j] -= MOD;
      }
    }
  }
  ll ans = 0;
  REP(i, N) {
    ans += dp[A[i] + DELTA][B[i] + DELTA];
    if (ans >= MOD) ans -= MOD;
    ans -= dp2[A[i] * 2][B[i] * 2];
    if (ans < 0) ans += MOD;
  }
  (ans *= inv(2)) %= MOD;
  PL(ans);
  return 0;
}

