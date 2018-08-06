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

typedef tuple<int, int, int, int> Edge;

#define W(x) get<0>(x)
#define U(x) get<1>(x)
#define V(x) get<2>(x)
#define ID(x) get<3>(x)
#define MT make_tuple

const int MAX_N = 1000 + 7;

struct Dsu {
  int par[MAX_N], sz[MAX_N], bk;

  void init(int n) {
    bk = n;
    REP1(i, 1, n) {
      par[i] = i;
      sz[i] = 1;
    }
  }

  int find(int x) {
    if (x == par[x]) return x;
    else return par[x] = find(par[x]);
  }

  bool merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return 0;
    if (sz[x] < sz[y]) swap(x, y);
    bk--;
    sz[x] += sz[y];
    par[y] = x;
    return 1;
  }

  bool query(int x, int y) {
    return find(x) == find(y);
  }
} dsu;

bool used[MAX_N];

int main() {
  int T;
  RI(T);
  REP1(kcase, 1, T) {
    int N, M;
    RI(N, M);
    vector<Edge> es_rg, es_bg, es_all;
    REP1(i, 1, M) {
      int u, v, w;
      char c[5];
      RI(u, v, w, c);
      es_all.PB(MT(w, u, v, i));
      if (c[0] == 'R') es_rg.PB(MT(w, u, v, i));
      if (c[0] == 'B') es_bg.PB(MT(w, u, v, i));
      if (c[0] == 'G') {
        es_rg.PB(MT(w, u, v, i));
        es_bg.PB(MT(w, u, v, i));
      }
    }
    printf("Case #%d:\n", kcase);
    sort(ALL(es_rg));
    sort(ALL(es_bg));
    sort(ALL(es_all));
    REP1(i, 1, N - 2) PL(-1);
    REP1(i, N - 1, M) {
      dsu.init(N);
      int ans = INF;
      int sum = 0;
      MS(used, 0);
      dsu.init(N);
      for (Edge e : es_rg) {
        if (dsu.merge(U(e), V(e))) {
          sum += W(e);
          used[ID(e)] = 1;
        }
      }
      int cnt = i - N + 1;
      if (dsu.bk == 1) {
        for (Edge e : es_all) {
          if (cnt == 0) break;
          if (!used[ID(e)]) {
            sum += W(e);
            cnt--;
          }
        }
        ans =  min(ans, sum);
      }
      sum = 0;
      MS(used, 0);
      dsu.init(N);
      for (Edge e : es_bg) {
        if (dsu.merge(U(e), V(e))) {
          sum += W(e);
          used[ID(e)] = 1;
        }
      }
      cnt = i - N + 1;
      if (dsu.bk == 1) {
        for (Edge e : es_all) {
          if (cnt == 0) break;
          if (!used[ID(e)]) {
            sum += W(e);
            cnt--;
          }
        }
        ans =  min(ans, sum);
      }
      if (ans == INF) ans = -1;
      PL(ans);
    }
  }
  return 0;
}

/*
1
4 6
1 2 1 R
1 3 1 R
1 2 3 B
1 3 3 B
1 4 3 B
1 4 4 G
*/
