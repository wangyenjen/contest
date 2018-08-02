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

const int MAX_N = 2000 + 7;
const ll MOD = 1000000000 + 7;

ll K;
ll dp[MAX_N][MAX_N];
ll fact[MAX_N * MAX_N];

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

ll C(ll n, ll m) {
  if (n < m) return 0;
  else return fact[n] * inv(fact[n - m] * fact[m] % MOD) % MOD;
}

ll dfs(int x, int y) {
  ll &res = dp[x][y];
  if (res != -1) return res;
  if (x == 0 && y == 0) return 1;
  res = 0;
  if (x > 0) {
    res += dfs(x - 1, y);
    if (res >= MOD) res -= MOD;
  }
  if (y > x) {
    res += C(x + y * (K - 1) - 1, K - 2) * dfs(x, y - 1) % MOD;
    if (res >= MOD) res -= MOD;
  }
  return res;
}

int main() {
  fact[0] = 1;
  REP1(i, 1, MAX_N * MAX_N - 1) fact[i] = fact[i - 1] * i % MOD;
  int N;
  RI(N, K);
  if (K == 1) PL(1);
  else {
    MS(dp, -1);
    PL(dfs(N, N) * fact[N] % MOD);
  }
  return 0;
}

