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

const double EPS = 1e-6;
const int MAX_N = 1000 + 7;

int dcmp(double x) {
  if (fabs(x) < EPS) return 0;
  else return x > 0 ? 1 : -1;
}

/* struct Dinic{
  static const int MXN = 10000;
  struct Edge {
    int v;
    double f;
    int re;
  };
  bool inq[MXN];
  int n,s,t,level[MXN];
  vector<Edge> E[MXN];
  void init(int _n, int _s, int _t){
    n = _n; s = _s; t = _t;
    for (int i=0; i<n; i++) E[i].clear();
  }
  void add_edge(int u, int v, double f){
    E[u].PB({v,f,SZ(E[v])});
    E[v].PB({u,0,SZ(E[u])-1});
  }
  bool BFS(){
    for (int i=0; i<n; i++) {
      level[i] = -1;
      inq[i] = 0;
    }
    queue<int> que;
    que.push(s);
    level[s] = 0;
    inq[s] = 1;
    while (!que.empty()){
      int u = que.front(); que.pop();
      for (auto it : E[u]){
        if (dcmp(it.f) > 0 && level[it.v] == -1){
          level[it.v] = level[u]+1;
          inq[it.v] = 1;
          que.push(it.v);
        }
      }
    }
    return level[t] != -1;
  }
  double DFS(int u, double nf){
    if (u == t || dcmp(nf) == 0) return nf;
    double res = 0;
    for (auto &it : E[u]){
      if (dcmp(it.f) > 0 && level[it.v] == level[u]+1){
        double tf = DFS(it.v, min(nf,it.f));
        res += tf; nf -= tf; it.f -= tf;
        E[it.v][it.re].f += tf;
        if (dcmp(nf) == 0) return res;
      }
    }
    if (!res) level[u] = -1;
    return res;
  }
  double flow(double res=0){
    while ( BFS() )
      res += DFS(s,1e30);
    return res;
  }
}flow; */

struct MaxFlow {
    static const int maxV = 100000;
    static const int maxE = 100000;
    int e, h[maxV], to[maxE], nxt[maxE];
    double cap[maxE];
    void init() {
        memset(h, -1, sizeof h);
        e = 0;
    }
    void add_edge(int u,int v, double c) {
        to[e] = v, nxt[e] = h[u], cap[e] = c, h[u] = e++;
        to[e] = u, nxt[e] = h[v], cap[e] = c, h[v] = e++;
    }

    int dis[maxV], que[maxE * 20], qh, qt;
    bool inq[maxV];
    int s, t;

    int sgn(double x) {
        return x < -EPS ? -1 : EPS < x;
    }

    bool bfs() {
        que[qh = qt = 0] = s;
        memset(inq, 0, sizeof inq);
        memset(dis, 0x3f, sizeof dis);
        dis[s] = 0;
        inq[s] = 1;
        while (qh <= qt) {
            int u = que[qh++];
            for (int i = h[u]; i != -1; i = nxt[i])
                if (cap[i] > EPS && !inq[to[i]]) {
                    int v = to[i];
                    inq[v] = 1;
                    dis[v] = dis[u] + 1;
                    que[++qt] = v;
                }
        }
        return dis[t] != 0x3f3f3f3f;
    }

    double dfs(int u, double a = 0) {
        if (u == t || sgn(a) == 0)
            return a;
        double flow = 0, f;
        for (int i = h[u]; i != -1; i = nxt[i])
            if (dis[to[i]] == dis[u]+1 && (f = dfs(to[i], min(a, cap[i]))) > 0) {
                flow += f;
                cap[i] -= f;
                cap[i^1] += f;
                a -= f;
                //if (a == 0) break;
                if (a == 0) {
                    return flow;
                }
            }
        dis[u] = -1;
        return flow;
    }

    double flow() {
        double res = 0;
        while (bfs())
            res += dfs(s, INF);
        return res;
    }
} flow;

int a[MAX_N], b[MAX_N];
double c[MAX_N];

int main() {
#ifdef ONLINE_JUDGE
  freopen("network.in", "r", stdin);
  freopen("network.out", "w", stdout);
#endif
  int n, m;
  RI(n, m);
  double mn = INF, mx = -INF;
  REP1(i, 1, m) {
    RI(a[i], b[i], c[i]);
    a[i]--, b[i]--;
    mn = min(mn, c[i]);
    mx = max(mx, c[i]);
  }
  double lb = mn, rb = mx;
  REP(times, 200) {
    double mid = (lb + rb) / 2.0;
    flow.init();
    flow.s = 0;
    flow.t = n - 1;
    double t = 0;
    REP1(i, 1, m) {
      if (dcmp(c[i] - mid) > 0) flow.add_edge(a[i], b[i], c[i] - mid);
      else t += c[i] - mid;
    }
    t += flow.flow();
    if (dcmp(t) < 0) rb = mid;
    else lb = mid;
  }
  vector<int> ans;
  REP1(i, 1, m) {
    if ((flow.inq[a[i]] ^ flow.inq[b[i]]) || dcmp(c[i] - (lb + rb) / 2.0) < 0) ans.PB(i);
  }
  PL(SZ(ans));
  REP(i, SZ(ans)) printf("%d%c", ans[i], " \n"[i == SZ(ans) - 1]);
  return 0;
}

