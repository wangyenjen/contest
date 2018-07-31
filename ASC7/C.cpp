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

const int MAX_N = 3000 + 7;

int A[MAX_N];
short dp[MAX_N][MAX_N];
short path[MAX_N][MAX_N];
vector<int> rd;
unordered_map<int, int> mapping;

int main() {
#ifdef ONLINE_JUDGE
  freopen("fibsubseq.in", "r", stdin);
  freopen("fibsubseq.out", "w", stdout);
#endif
  int N;
  RI(N);
  REP1(i, 1, N) {
    RI(A[i]);
    rd.PB(A[i]);
  }
  rd.push_back(-INF);
  sort(ALL(rd));
  rd.erase(unique(ALL(rd)), rd.end());
  REP(i, SZ(rd)) mapping[rd[i]] = i;
  if (N == 1) {
    PL(1);
    PL(A[1]);
    return 0;
  }
  int ans = 0;
  REP1(i, 1, N) {
    REP1(j, 1, i - 1) {
      if (mapping.count(A[i] - A[j]) && dp[j][mapping[A[i] - A[j]]]) {
        if (dp[i][mapping[A[j]]]) {
          if (dp[j][mapping[A[i] - A[j]]] + 1 > dp[i][mapping[A[j]]]) {
            dp[i][mapping[A[j]]] = dp[j][mapping[A[i] - A[j]]] + 1;
            path[i][mapping[A[j]]] = j;
          }
        }
        else {
          dp[i][mapping[A[j]]] = dp[j][mapping[A[i] - A[j]]] + 1;
          path[i][mapping[A[j]]] = j;
        }
      }
      else {
        if (!dp[i][mapping[A[j]]]) {
          dp[i][mapping[A[j]]] = 2;
          path[i][mapping[A[j]]] = j;
        }
      }
      ans = max(ans, (int)dp[i][mapping[A[j]]]);
    }
  }
  PL(ans);
  int p1 = 0, p2 = 0;
  REP1(i, 1, N) {
    REP1(j, 1, SZ(rd) - 1) {
      if (dp[i][j] == ans) {
        p1 = i;
        p2 = j;
        break;
      }
    }
    if (p1) break;
  }
  vector<int> vans;
  while (1) {
    vans.PB(A[p1]);
    if (path[p1][p2]) {
      int t = path[p1][p2];
      p2 = mapping[A[p1] - rd[p2]];
      p1 = t;
    }
    else break;
  }
  reverse(ALL(vans));
  REP(i, SZ(vans)) printf("%d%c", vans[i], " \n"[i == SZ(vans) - 1]);
  return 0;
}
