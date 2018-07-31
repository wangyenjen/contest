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

struct Bign {
    vector<int> num;
    Bign() {
        num.clear();
    }
    Bign(int x) {
        num.clear();
        while(x) {
            num.PB(x % 10);
            x /= 10;
        }
        if(!SZ(num)) num.PB(0);
    }
    Bign(char *p) {
        num.clear();
        while(*p) {
            num.PB(*p - '0');
            p++;
        }
        reverse(ALL(num));
        if(!SZ(num)) num.PB(0);
    }
    bool operator < (const Bign &rhs) const {
        if(SZ(num) != SZ(rhs.num)) return SZ(num) < SZ(rhs.num);
        for(int i = SZ(num) - 1; i >= 0; i--) {
            if(num[i] != rhs.num[i]) return num[i] < rhs.num[i];
        }
        return 0;
    }
    bool operator > (const Bign &rhs) const {
        if(SZ(num) != SZ(rhs.num)) return SZ(num) > SZ(rhs.num);
        for(int i = SZ(num) - 1; i >= 0; i--) {
            if(num[i] != rhs.num[i]) return num[i] > rhs.num[i];
        }
        return 0;
    }
    bool operator == (const Bign &rhs) const {
        if(SZ(num) != SZ(rhs.num)) return 0;
        for(int i = SZ(num) - 1; i >= 0; i--) {
            if(num[i] != rhs.num[i]) return 0;
        }
        return 1;
    }
    bool operator <= (const Bign &rhs) const {
        return *this < rhs || *this == rhs;
    }
    bool operator >= (const Bign &rhs) const {
        return *this > rhs || *this == rhs;
    }
    bool operator != (const Bign &rhs) const {
        return !(*this == rhs);
    }
};

inline Bign operator + (const Bign &a , const Bign &b) {
    Bign c;
    REP(i , max(SZ(a.num) , SZ(b.num))) {
        if(i >= SZ(c.num)) c.num.PB(0);
        if(SZ(a.num) > i) c.num[i] += a.num[i];
        if(SZ(b.num) > i) c.num[i] += b.num[i];
        if(c.num[i] >= 10) {
            if(i + 1 >= SZ(c.num)) c.num.PB(0);
            c.num[i + 1] += c.num[i] / 10;
            c.num[i] %= 10;
        }
    }
    while(SZ(c.num) && c.num.back() == 0) c.num.pop_back();
    if(!SZ(c.num)) c.num.PB(0);
    return c;
}

inline Bign operator * (const Bign &a , const Bign &b) {
    Bign c;
    REP(i , SZ(a.num)) {
        REP(j , SZ(b.num)) {
            if(i + j >= SZ(c.num)) c.num.PB(0);
            c.num[i + j] += a.num[i] * b.num[j];
        }
    }
    REP(i , SZ(c.num)) {
        if(c.num[i] >= 10) {
            if(i + 1 >= SZ(c.num)) c.num.PB(0);
            c.num[i + 1] += c.num[i] / 10;
            c.num[i] %= 10;
        }
    }
    while(SZ(c.num) && c.num.back() == 0) c.num.pop_back();
    if(!SZ(c.num)) c.num.PB(0);
    return c;
}

inline Bign operator - (const Bign &a , const Bign &b) { // a >= b
    Bign c;
    c.num = a.num;
    REP(i , SZ(c.num)) {
        if(SZ(b.num) > i) c.num[i] -= b.num[i];
        if(c.num[i] < 0) {
            c.num[i + 1]--;
            c.num[i] += 10;
        }
    }
    while(SZ(c.num) && c.num.back() == 0) c.num.pop_back();
    if(!SZ(c.num)) c.num.PB(0);
    return c;
}

inline void print(const Bign &x) {
    for(int i = SZ(x.num) - 1; i >= 0; i--) putchar(x.num[i] + '0');
    putchar('\n');
}

inline Bign operator / (const Bign &a , const Bign &b) {
    Bign c , r(0);
    for(int i = SZ(a.num) - 1; i >= 0; i--) {
        r = (r * Bign(10)) + Bign(a.num[i]);
        c.num.PB(0);
        while(r >= b) {
            c.num.back()++;
            r = r - b;
        }
    }
    reverse(ALL(c.num));
    while(SZ(c.num) && c.num.back() == 0) c.num.pop_back();
    if(!SZ(c.num)) c.num.PB(0);
    return c;
}

inline Bign operator % (const Bign &a , const Bign &b) {
    return a - ((a / b) * b);
}

Bign gcd(Bign a , Bign b) {
    return b == Bign(0) ? a : gcd(b , a % b);
}

const int MAX_N = 100 + 7;

char A[MAX_N], B[MAX_N];

int main() {
  freopen("toral.in", "r", stdin);
  freopen("toral.out", "w", stdout);
  RI(A, B);
  print(gcd(Bign(A), Bign(B)));
  return 0;
}
