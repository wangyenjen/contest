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

const int MAX_N = 30000 + 7;

struct Matrix {
  int a[2][2];

  Matrix(int v = 0) {
    MS(a, 0);
    a[0][0] = a[1][1] = v;
  }

  int& operator () (const int x, const int y) {
    return a[x][y];
  }
};

int R;

Matrix operator * (Matrix a, Matrix b) {
  Matrix c(0);
  REP(k, 2) REP(i, 2) REP(j, 2) (c(i, j) += a(i, k) * b(k, j)) %= R;
  return c;
}

Matrix A[MAX_N];
Matrix tr[MAX_N<<2];

void build(int o, int l, int r) {
  if (l == r) tr[o] = A[l];
  else {
    int m = (l + r) >> 1;
    build(LC);
    build(RC);
    tr[o] = tr[o<<1] * tr[o<<1|1];
  }
}

Matrix query(int o, int l, int r, int ql, int qr) {
  if (ql <= l && r <= qr) return tr[o];
  int m = (l + r) >> 1;
  if (qr <= m) return query(LC, ql, qr);
  else if (m < ql) return query(RC, ql, qr);
  else return query(LC, ql, qr) * query(RC, ql, qr);
}

int main() {
#ifdef ONLINE_JUDGE
  freopen("crypto.in", "r", stdin);
  freopen("crypto.out", "w", stdout);
#endif
  int N, M;
  RI(R, N, M);
  REP1(i, 1, N) {
    REP(j, 2) {
      REP(k, 2) RI(A[i](j, k));
    }
  }
  build(1, 1, N);
  while (M--) {
    int l, r;
    RI(l, r);
    Matrix a = query(1, 1, N, l, r);
    PL(a(0, 0), a(0, 1));
    PL(a(1, 0), a(1, 1));
    if (M) PL();
  }
  return 0;
}

