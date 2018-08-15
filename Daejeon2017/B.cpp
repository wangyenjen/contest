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

map<tuple<int, int, int>, int> ans;

int main() {
  ans[make_tuple(1, 1, 1)] = 0;
  ans[make_tuple(1, 1, 2)] = 287;
  ans[make_tuple(1, 1, 3)] = 311;
  ans[make_tuple(1, 1, 4)] = 80;
  ans[make_tuple(1, 2, 1)] = 96;
  ans[make_tuple(1, 2, 2)] = 609;
  ans[make_tuple(1, 2, 3)] = 675;
  ans[make_tuple(1, 2, 4)] = 76;
  ans[make_tuple(1, 3, 1)] = 315;
  ans[make_tuple(1, 3, 2)] = 543;
  ans[make_tuple(1, 3, 3)] = 455;
  ans[make_tuple(1, 3, 4)] = 351;
  ans[make_tuple(1, 4, 1)] = 342;
  ans[make_tuple(1, 4, 2)] = 188;
  ans[make_tuple(1, 4, 3)] = 204;
  ans[make_tuple(1, 4, 4)] = 286;
  ans[make_tuple(2, 1, 1)] = 47;
  ans[make_tuple(2, 1, 2)] = 0;
  ans[make_tuple(2, 1, 3)] = 175;
  ans[make_tuple(2, 1, 4)] = 55;
  ans[make_tuple(2, 2, 1)] = 94;
  ans[make_tuple(2, 2, 2)] = 630;
  ans[make_tuple(2, 2, 3)] = 516;
  ans[make_tuple(2, 2, 4)] = 69;
  ans[make_tuple(2, 3, 1)] = 431;
  ans[make_tuple(2, 3, 2)] = 364;
  ans[make_tuple(2, 3, 3)] = 615;
  ans[make_tuple(2, 3, 4)] = 171;
  ans[make_tuple(2, 4, 1)] = 177;
  ans[make_tuple(2, 4, 2)] = 252;
  ans[make_tuple(2, 4, 3)] = 116;
  ans[make_tuple(2, 4, 4)] = 172;
  ans[make_tuple(3, 1, 1)] = 55;
  ans[make_tuple(3, 1, 2)] = 175;
  ans[make_tuple(3, 1, 3)] = 0;
  ans[make_tuple(3, 1, 4)] = 47;
  ans[make_tuple(3, 2, 1)] = 69;
  ans[make_tuple(3, 2, 2)] = 516;
  ans[make_tuple(3, 2, 3)] = 630;
  ans[make_tuple(3, 2, 4)] = 94;
  ans[make_tuple(3, 3, 1)] = 171;
  ans[make_tuple(3, 3, 2)] = 615;
  ans[make_tuple(3, 3, 3)] = 364;
  ans[make_tuple(3, 3, 4)] = 431;
  ans[make_tuple(3, 4, 1)] = 172;
  ans[make_tuple(3, 4, 2)] = 116;
  ans[make_tuple(3, 4, 3)] = 252;
  ans[make_tuple(3, 4, 4)] = 177;
  ans[make_tuple(4, 1, 1)] = 80;
  ans[make_tuple(4, 1, 2)] = 311;
  ans[make_tuple(4, 1, 3)] = 287;
  ans[make_tuple(4, 1, 4)] = 0;
  ans[make_tuple(4, 2, 1)] = 76;
  ans[make_tuple(4, 2, 2)] = 675;
  ans[make_tuple(4, 2, 3)] = 609;
  ans[make_tuple(4, 2, 4)] = 96;
  ans[make_tuple(4, 3, 1)] = 351;
  ans[make_tuple(4, 3, 2)] = 455;
  ans[make_tuple(4, 3, 3)] = 543;
  ans[make_tuple(4, 3, 4)] = 315;
  ans[make_tuple(4, 4, 1)] = 286;
  ans[make_tuple(4, 4, 2)] = 204;
  ans[make_tuple(4, 4, 3)] = 188;
  ans[make_tuple(4, 4, 4)] = 342;
  int x, a, b;
  RI(x, a, b);
  PL(ans[make_tuple(x, a, b)]);
  return 0;
}
