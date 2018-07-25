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

const int MAX_N = 40 + 7;

struct Dinic{
  static const int MXN = 10000;
  struct Edge{ int v,f,re; };
  int n,s,t,level[MXN];
  vector<Edge> E[MXN];
  void init(int _n, int _s, int _t){
    n = _n; s = _s; t = _t;
    for (int i=0; i<n; i++) E[i].clear();
  }
  void add_edge(int u, int v, int f){
    E[u].PB({v,f,SZ(E[v])});
    E[v].PB({u,0,SZ(E[u])-1});
  }
  bool BFS(){
    for (int i=0; i<n; i++) level[i] = -1;
    queue<int> que;
    que.push(s);
    level[s] = 0;
    while (!que.empty()){
      int u = que.front(); que.pop();
      for (auto it : E[u]){
        if (it.f > 0 && level[it.v] == -1){
          level[it.v] = level[u]+1;
          que.push(it.v);
        }
      }
    }
    return level[t] != -1;
  }
  int DFS(int u, int nf){
    if (u == t) return nf;
    int res = 0;
    for (auto &it : E[u]){
      if (it.f > 0 && level[it.v] == level[u]+1){
        int tf = DFS(it.v, min(nf,it.f));
        res += tf; nf -= tf; it.f -= tf;
        E[it.v][it.re].f += tf;
        if (nf == 0) return res;
      }
    }
    if (!res) level[u] = -1;
    return res;
  }
  int flow(int res=0){
    while ( BFS() )
      res += DFS(s,2147483647);
    return res;
  }
}flow;

int R, C;
char A[MAX_N][MAX_N];
int cx[MAX_N], cy[MAX_N];

int calc(int x, int y) {
  REP1(i, 1, R) {
    cx[i] = x;
    REP1(j, 1, C) if (A[i][j] == '1') cx[i]--;
  }
  REP1(j, 1, C) {
    cy[j] = y;
    REP1(i, 1, R) if (A[i][j] == '1') cy[j]--;
  }

  int res = 0;

  // 0 -> 1
  int st = 0, ed = R + C + 1;
  flow.init(R + C + 2, st, ed);
  REP1(i, 1, R) if (cx[i] > 0) flow.add_edge(st, i, cx[i]);
  REP1(i, 1, C) if (cy[i] > 0) flow.add_edge(R + i, ed, cy[i]);
  REP1(i, 1, R) REP1(j, 1, C) if (A[i][j] == '0') flow.add_edge(i, R + j, 1);
  if (flow.flow()) {
    REP1(i, 1, R) {
      for (auto e : flow.E[i]) {
        if (e.f == 0 && R < e.v && e.v <= R + C) {
          cx[i]--;
          cy[e.v - R]--;
          res++;
        }
      }
    }
  }

  // 1 -> 0
  flow.init(R + C + 2, st, ed);
  REP1(i, 1, R) if (cx[i] < 0) flow.add_edge(st, i, -cx[i]);
  REP1(i, 1, C) if (cy[i] < 0) flow.add_edge(R + i, ed, -cy[i]);
  REP1(i, 1, R) REP1(j, 1, C) if (A[i][j] == '1') flow.add_edge(i, R + j, 1);
  if (flow.flow()) {
    REP1(i, 1, R) {
      for (auto e : flow.E[i]) {
        if (e.f == 0 && R < e.v && e.v <= R + C) {
          cx[i]++;
          cy[e.v - R]++;
          res++;
        }
      }
    }
  }

  int tx = 0, ty = 0;
  REP1(i, 1, R) tx += abs(cx[i]);
  REP1(i, 1, C) ty += abs(cy[i]);
  res += tx + ty + min(tx, ty);
  return res;
}

int main() {
  int T;
  RI(T);
  REP(kcase, T) {
    RI(R, C);
    REP1(i, 1, R) SR(A[i] + 1);
    int ans = R * C;
    REP1(i, 0, C) {
      int t = i * R;
      if (t % C) continue;
      ans = min(ans, calc(i, t / C));
    }
    printf("Case %d: %d\n", kcase + 1, ans);
  }
  return 0;
}
