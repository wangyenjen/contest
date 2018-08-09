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

const int MAX_N = 100000 + 7;

int stx, sty;
bool in_cycle[MAX_N];
vector<int> G[MAX_N];
int par[MAX_N], dp[MAX_N], dep[MAX_N];

void dfs(int u, int fa = 0, int val = 1) {
  dp[u] = val;
  par[u] = fa;
  dep[u] = dep[fa] + 1;
  for (int v : G[u]) {
    if (v == fa) continue;
    if (dep[v]) stx = u, sty = v;
    else {
      dfs(v, u, -val);
      dp[u] += dp[v];
    }
  }
}

int get_lca(int x, int y) {
  while (dep[x] > dep[y]) x = par[x];
  while (dep[y] > dep[x]) y = par[y];
  while (x != y) x = par[x], y = par[y];
  return x;
}

int main() {
  int N, M;
  RI(N, M);
  REP(i, M) {
    int u, v;
    RI(u, v);
    G[u].PB(v);
    G[v].PB(u);
  }
  dfs(1);
  if (M == N - 1) {
    if (dp[1]) {
      PL(-1);
      return 0;
    }
    int ans = 0;
    REP1(i, 1, N) ans += abs(dp[i]);
    PL(ans);
    return 0;
  }
  if ((dep[stx] - dep[sty]) & 1) {
    if (dp[1]) {
      PL(-1);
      return 0;
    }
    vector<int> vs;
    int lca = get_lca(stx, sty);
    for (int u = stx; u != lca; u = par[u]) {
      vs.PB(dp[u]);
      in_cycle[u] = 1;
    }
    for (int u = sty; u != lca; u = par[u]) {
      vs.PB(-dp[u]);
      in_cycle[u] = 1;
    }
    vs.PB(0);
    int mid = SZ(vs) / 2;
    nth_element(vs.begin(), vs.begin() + mid, vs.end());
    int ans = 0;
    REP1(i, 1, N) {
      if (!in_cycle[i]) ans += abs(dp[i]);
    }
    for (int x : vs) ans += abs(x - vs[mid]);
    PL(ans);
  }
  else {
    if (dp[1] & 1) {
      PL(-1);
      return 0;
    }
    int t = -dp[1] / 2;
    int ans = abs(t);
    for (int u = stx; u; u = par[u]) dp[u] += t;
    for (int u = sty; u; u = par[u]) dp[u] += t;
    REP1(i, 1, N) ans += abs(dp[i]);
    PL(ans);
  }
  return 0;
}
