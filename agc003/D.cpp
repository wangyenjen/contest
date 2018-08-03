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
const ll INF64 = (ll)1e10;

// random function
inline int RAND() {
  static int x = 880301;
  return (x = x * 0xdefaced + 1) % 0x7fffffff;
}
/// }}}

const int MAX_N = 100000 + 7;

ll A[MAX_N];
bool vis[MAX_N];
vector<int> prime;

ll norm(ll x) {
  for (int p : prime) {
    ll t = 1ll * p * p * p;
    if (t > x) break;
    while (x % t == 0) x /= t;
  }
  return x;
}

ll mul(ll a, ll b) {
  if (INF64 / b < a) return INF64;
  else return a * b;
}

ll conj(ll x) {
  ll res = 1;
  for (int p : prime) {
    if (1ll * p * p > x) break;
    if(x % p == 0) {
      if ((x / p) % p == 0) res = mul(res , p) , x /= p , x /= p;
      else res = mul(res , mul(p , p)) , x /= p;
    }
  }
  if (x > 1) res = mul(res, mul(x, x));
  return res;
}

int main() {
  REP1(i, 2, MAX_N - 1) {
    if (vis[i]) continue;
    prime.PB(i);
    for (int j = i + i; j < MAX_N; j += i) vis[j] = 1;
  }
  int N;
  RI(N);
  unordered_map<ll, int> cnt;
  REP(i, N) {
    RI(A[i]);
    A[i] = norm(A[i]);
    cnt[A[i]]++;
  }
  int ans = 0;
  unordered_set<ll> used;
  for (auto it : cnt) {
    ll x = it.F;
    if (used.count(x)) continue;
    ll y = conj(x);
    used.insert(x);
    if (x == y) {
      ans++;
      continue;
    }
    if (!cnt.count(y)) {
      ans += it.S;
      continue;
    }
    ans += max(it.S, cnt[y]);
    used.insert(y);
  }
  PL(ans);
  return 0;
}
