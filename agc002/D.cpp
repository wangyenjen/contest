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

typedef tuple<int, int, int, int> tiiii;

#define ID(x) get<0>(x)
#define X(x) get<1>(x)
#define Y(x) get<2>(x)
#define Z(x) get<3>(x)

const int MAX_N = 100000 + 7;

pii es[MAX_N];
int ans[MAX_N];
int par[MAX_N], sz[MAX_N];
vector<pair<int*, int> > stk_par, stk_sz;

void init(int n) {
  REP1(i, 1, n) par[i] = i, sz[i] = 1;
  stk_par.clear();
  stk_sz.clear();
}

int find(int x) {
  while (x != par[x]) x = par[x];
  return x;
}

bool merge(int x, int y) {
  x = find(x);
  y = find(y);
  if (x == y) return 0;
  if (sz[x] < sz[y]) swap(x, y);
  stk_sz.PB(MP(&sz[x], sz[x]));
  stk_par.PB(MP(&par[y], par[y]));
  sz[x] += sz[y];
  par[y] = x;
  return 1;
}

bool undo() {
  if (stk_sz.empty() || stk_par.empty()) return 0;
  pair<int*, int> p_par = stk_par.back();
  pair<int*, int> p_sz = stk_sz.back();
  stk_par.pop_back();
  stk_sz.pop_back();
  *p_par.F  = p_par.S;
  *p_sz.F = p_sz.S;
  return 1;
}

bool query(int x, int y) {
  return find(x) == find(y);
}

int get_sz(int x) {
  x = find(x);
  return sz[x];
}

int get_sz(int x, int y) {
  if (query(x, y)) return get_sz(x);
  else return get_sz(x) + get_sz(y);
}

void tot_bs(vector<tiiii> &qs, int lb, int rb) {
  if (lb == rb) {
    for (tiiii t : qs) ans[ID(t)] = lb;
  }
  else {
    int mid =  (lb + rb) >> 1;
    int op_cnt = 0;
    REP1(i, lb, mid) {
      if (merge(es[i].F, es[i].S)) op_cnt++;
    }
    vector<tiiii> qls, qrs;
    for (tiiii t : qs) {
      if (get_sz(X(t), Y(t)) >= Z(t)) qls.PB(t);
      else qrs.PB(t);
    }
    tot_bs(qrs, mid + 1, rb);
    while (op_cnt--) undo();
    tot_bs(qls, lb, mid);
  }
  qs.clear();
  qs.shrink_to_fit();
}

int main() {
  int N, M;
  RI(N, M);
  REP1(i, 1, M) RI(es[i].F, es[i].S);
  int Q;
  RI(Q);
  vector<tiiii> qs;
  REP(i, Q) {
    int x, y, z;
    RI(x, y, z);
    qs.emplace_back(i, x, y, z);
  }
  init(N);
  tot_bs(qs, 1, M);
  REP(i, Q) PL(ans[i]);
  return 0;
}
