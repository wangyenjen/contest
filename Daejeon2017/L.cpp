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

typedef tuple<ll, int, int> tlii;

#define MT make_tuple

const int MAX_N = 50 + 7;

vector<pii> G[3][MAX_N];
int p, n[3], h[3][MAX_N];
ll dp[MAX_N * MAX_N * MAX_N][1 << 3];
bool vis[MAX_N * MAX_N * MAX_N][1 << 3];

void decode(int code, int res[]) {
  for (int i = p - 1; i >= 0; i--) {
    res[i] = code % n[i];
    code /= n[i];
  }
}

int encode(int a[]) {
  int res = 0;
  REP(i, p) res = res * n[i] + a[i];
  return res;
}

int main() {
  RI(p);
  int pos[3];
  REP(t, p) {
    int m;
    RI(n[t], m);
    REP(i, n[t]) RI(h[t][i]);
    REP(i, m) {
      int u, v, w;
      RI(u, v, w);
      G[t][u - 1].PB(MP(v - 1, w));
    }
    RI(pos[t]);
    pos[t]--;
  }
  int ed = encode(pos);
  MS(dp, INF64);
  dp[0][0] = 0;
  priority_queue<tlii, vector<tlii>, greater<tlii> > pq;
  pq.push(MT(0, 0, 0));
  while (!pq.empty()) {
    ll cost;
    int now, state;
    tie(cost, now, state) = pq.top();
    pq.pop();
    if (vis[now][state]) continue;
    vis[now][state] = 1;
    if (now == ed && state == 0) {
      PL(cost);
      return 0;
    }
    decode(now, pos);
    bool flag = 0;
    REP(t, p) {
      if (state & (1 << t)) continue;
      int u = pos[t];
      for (pii pp : G[t][u]) {
        int v, w;
        tie(v, w) = pp;
        pos[t] = v;
        int n_now = encode(pos);
        int n_state = state | (1<<t);
        ll n_cost = cost + w;
        if (dp[n_now][n_state] > n_cost) {
          dp[n_now][n_state] = n_cost;
          pq.emplace(n_cost, n_now, n_state);
        }
        pos[t] = u;
      }
      int n_now = now;
      int n_state = state | (1<<t);
      ll n_cost = cost + h[t][u];
      if (dp[n_now][n_state] > n_cost) {
        dp[n_now][n_state] = n_cost;
        pq.emplace(n_cost, n_now, n_state);
      }
      flag = 1;
      break;
    }
    if (flag) continue;
    int n_now = now;
    int n_state = 0;
    ll n_cost = cost;
    if (dp[n_now][n_state] > n_cost) {
      dp[n_now][n_state] = n_cost;
      pq.emplace(n_cost, n_now, n_state);
    }
  }
  return 0;
}
