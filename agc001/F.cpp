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

const int MAX_N = 500000 + 7;

int tr[MAX_N<<2];

void modify(int o, int l, int r, int p, int v) {
  if (l == r) tr[o] = v;
  else {
    int m = (l + r) >> 1;
    if (p <= m) modify(LC, p, v);
    else modify(RC, p, v);
    tr[o] = min(tr[o<<1], tr[o<<1|1]);
  }
}

int query(int o, int l, int r, int ql, int qr) {
  if (ql <= l && r <= qr) return tr[o];
  int m = (l + r) >> 1;
  if (qr <= m) return query(LC, ql, qr);
  else if (m < ql) return query(RC, ql, qr);
  else return min(query(LC, ql, qr), query(RC, ql, qr));
}

int ans[MAX_N];
int deg[MAX_N];
vector<int> G[MAX_N];
int P[MAX_N], Q[MAX_N];

int main() {
  int N, K;
  RI(N, K);
  REP1(i, 1, N) {
    RI(P[i]);
    Q[P[i]] = i;
  }
  MS(tr, INF);
  for (int i = N; i >= 1; i--) {
    int p =  query(1, 1, N, max(1, Q[i] - K + 1), Q[i]);
    if (p != INF) {
      G[Q[i]].PB(Q[p]);
      deg[Q[p]]++;
    }
    p =  query(1, 1, N, Q[i], min(N, Q[i] + K - 1));
    if (p != INF) {
      G[Q[i]].PB(Q[p]);
      deg[Q[p]]++;
    }
    modify(1, 1, N, Q[i], i);
  }
  priority_queue<int, vector<int>, greater<int> > pq;
  REP1(i, 1, N) {
    if (deg[i] == 0) pq.push(i);
  }
  int now_id = 0;
  while (!pq.empty()) {
    int u = pq.top();
    ans[u] = ++now_id;
    pq.pop();
    for (int v : G[u]) {
      if (--deg[v] == 0) pq.push(v);
    }
  }
  REP1(i, 1, N) PL(ans[i]);
  return 0;
}

