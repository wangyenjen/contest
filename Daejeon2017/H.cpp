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

using cplx = complex<double>;

constexpr int maxn = 1<<20;
constexpr int MAX_N = maxn;
constexpr double pi = acos(-1.0);

void fft(cplx *a, int n, bool inverse) {
	static cplx tmp[maxn];
	if (n == 1) return;
	copy_n(a, n, tmp);
	for (int i = 0; i < n; i++)
		a[(i & 1) ? (n >> 1) + (i >> 1) : (i >> 1)] = tmp[i];
	cplx *a1 = a, *a2 = a + (n >> 1);
	fft(a1, n >> 1, inverse);
	fft(a2, n >> 1, inverse);
	cplx w_base = polar(1.0, 2.0 * pi / n);
	if (inverse)
		w_base = conj(w_base);
	cplx w(1.0);
	for (int i = 0; (i << 1) < n; i++, w *= w_base) {
		tmp[i] = a1[i] + w * a2[i];
		tmp[(n >> 1) + i] = a1[i] - w * a2[i];
	}
	copy_n(tmp, n, a);
}

int mult(cplx *a, int la, cplx *b, int lb, cplx *c) {
	int n = 2;
	while (n < la + lb) n <<= 1;
	fill(a + la, a + n, cplx());
	fill(b + lb, b + n, cplx());
	fft(a, n, false);
	fft(b, n, false);
	for (int i = 0; i < n; i++) c[i] = a[i] * b[i];
	fft(c, n, true);
	for (int i = 0; i < n; i++) c[i] /= n;
	return la + lb - 1;
}

int ans[MAX_N];
char s[MAX_N], t[MAX_N];
cplx a[MAX_N], b[MAX_N], c[MAX_N];

int main() {
  int n, m;
  RI(n, m);
  SR(s);
  SR(t);
  reverse(t, t + m);
  REP(i, n) a[i] = cplx(s[i] == 'S', 0);
  REP(i, m) b[i] = cplx(t[i] == 'R', 0);
  int len = mult(a, n, b, m, c);
  for (int i = m - 1; i < len; i++) ans[i - m + 1] += int(real(c[i]) + 0.5);

  REP(i, n) a[i] = cplx(s[i] == 'R', 0);
  REP(i, m) b[i] = cplx(t[i] == 'P', 0);
  len = mult(a, n, b, m, c);
  for (int i = m - 1; i < len; i++) ans[i - m + 1] += int(real(c[i]) + 0.5);

  REP(i, n) a[i] = cplx(s[i] == 'P', 0);
  REP(i, m) b[i] = cplx(t[i] == 'S', 0);
  len = mult(a, n, b, m, c);
  for (int i = m - 1; i < len; i++) ans[i - m + 1] += int(real(c[i]) + 0.5);

  PL(*max_element(ans, ans + n));

  return 0;
}

