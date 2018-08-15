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

const int MAX_N = 5000 + 7;

int N;
vector<int> G[MAX_N];
int dp1[MAX_N][MAX_N];
int dp2[MAX_N][MAX_N];
int sum[MAX_N][MAX_N];

void dfs(int u, int fa = 0) {
  for (int v : G[u]) {
    if (v == fa) continue;
    dfs(v, u);
    REP(i, N + 1) sum[u][i] += dp2[v][i];
  }
  for (int v : G[u]) {
    if (v == fa) continue;
    REP1(i, 1, N) dp1[u][i - 1] = min(dp1[u][i - 1], dp1[v][i] + (sum[u][i - 1] - dp2[v][i - 1]));
  }
  REP1(i, 1, N) {
    dp1[u][i] = min(dp1[u][i], sum[u][i] + i);
    dp2[u][i] = min(dp2[u][i], sum[u][i - 1]);
  }
  for (int i = N - 1; i >= 0; i--) dp1[u][i] = min(dp1[u][i], dp1[u][i + 1]);
  dp2[u][0] = dp1[u][0];
  for (int i = 1; i <= N; i++) dp2[u][i] = min(dp2[u][i], dp2[u][i - 1]);
}

int main() {
  RI(N);
  REP(i, N - 1) {
    int u, v;
    RI(u, v);
    G[u].PB(v);
    G[v].PB(u);
  }
  MS(dp1, INF);
  MS(dp2, INF);
  dfs(1);
  PL(min(dp1[1][0], dp2[1][0]));
  return 0;
}
