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

typedef double D;

const D eps = 1e-4;
const D PI = acos(-1.0);
const int MAX_N = 10 + 7;
const D DX[4] = {0, 0, 1, -1};
const D DY[4] = {-1, 1, 0, 0};

inline int fi (double a) {
    if (a > eps) return 1;
    else if (a >= -eps) return 0;
    else return -1;
}

class Vector {
public:
    double x, y;
    Vector (void) {}
    Vector (double x0, double y0) : x(x0), y(y0) {}
    double operator * (const Vector& a) const { return x * a.y - y * a.x; }
    double operator % (const Vector& a) const { return x * a.x + y * a.y; }
    Vector verti (void) const { return Vector(-y, x); }
    double length (void) const { return sqrt(x * x + y * y); }
    Vector adjust (double len)
    {
        double ol = len / length();
        return Vector(x * ol, y * ol);
    }
    Vector oppose (void) { return Vector(-x, -y); }
};

class point {
public:
    double x, y;
    point (void) {}
    point (double x0, double y0) : x(x0), y(y0) {}
    Vector operator - (const point& a) const { return Vector(x - a.x, y - a.y); }
    point operator + (const Vector& a) const { return point(x + a.x, y + a.y); }
};

class segment {
public:
    point a, b;
    segment (void) {}
    segment (point a0, point b0) : a(a0), b(b0) {}
    point intersect (const segment& s) const
    {
        Vector v1 = s.a - a, v2 = s.b - a, v3 = s.b - b, v4 = s.a - b;
        double s1 = v1 * v2, s2 = v3 * v4;
        double se = s1 + s2;
        s1 /= se, s2 /= se;
        return point(a.x * s2 + b.x * s1, a.y * s2 + b.y * s1);
    }
    point pverti (const point& p) const
    {
        Vector t = (b - a).verti();
        segment uv(p, p + t);
        return intersect(uv);
    }
    bool on_segment (const point& p) const
    {
        if (fi(min(a.x, b.x) - p.x) <= 0 && fi(p.x - max(a.x, b.x)) <= 0 &&
            fi(min(a.y, b.y) - p.y) <= 0 && fi(p.y - max(a.y, b.y)) <= 0) return true;
        else return false;
    }
};

double radius;
point polygon[510];

double kuras_area (point a, point b, double cx, double cy)
{
    point ori(cx, cy);
    int sgn = fi((b - ori) * (a - ori));
    double da = (a - ori).length(), db = (b - ori).length();
    int ra = fi(da - radius), rb = fi(db - radius);
    double angle = acos(((b - ori) % (a - ori)) / (da * db));
    segment t(a, b); point h, u; Vector seg;
    double ans, dlt, mov, tangle;

    if (fi(da) == 0 || fi(db) == 0) return 0;
    else if (sgn == 0) return 0;
    else if (ra <= 0 && rb <= 0) return fabs((b - ori) * (a - ori)) / 2 * sgn;
    else if (ra >= 0 && rb >= 0)
    {
        h = t.pverti(ori);
        dlt = (h - ori).length();
        if (!t.on_segment(h) || fi(dlt - radius) >= 0)
            return radius * radius * (angle / 2) * sgn;
        else
        {
            ans = radius * radius * (angle / 2);
            tangle = acos(dlt / radius);
            ans -= radius * radius * tangle;
            ans += radius * sin(tangle) * dlt;
            return ans * sgn;
        }
    }
    else
    {
        h = t.pverti(ori);
        dlt = (h - ori).length();
        seg = b - a;
        mov = sqrt(radius * radius - dlt * dlt);
        seg = seg.adjust(mov);
        if (t.on_segment(h + seg)) u = h + seg;
        else u = h + seg.oppose();
        if (ra == 1) swap(a, b);
        ans = fabs((a - ori) * (u - ori)) / 2;
        tangle = acos(((u - ori) % (b - ori)) / ((u - ori).length() * (b - ori).length()));
        ans += radius * radius * (tangle / 2);
        return ans * sgn;
    }
}

int n;

int dcmp(D x) {
    return fabs(x) < eps ? 0 : x > 0 ? 1 : -1;
}

D calc(double cx, double cy) {
    D area = 0;
    for (int i = 0; i < n; i++)
        area += kuras_area(polygon[i], polygon[(i + 1) % n], cx, cy);
    return fabs(area);
}

int main() {
#ifdef ONLINE_JUDGE
  freopen("mammoth.in", "r", stdin);
  freopen("mammoth.out", "w", stdout);
#endif
  n = 4;
  double cx, cy;
  RI(cx, cy, radius);
  double x1, y1, x2, y2;
  RI(x1, y1, x2, y2);
  if (x1 > x2) swap(x1, x2);
  if (y1 > y2) swap(y1, y2);
  polygon[0] = point(x1, y1);
  polygon[1] = point(x2, y1);
  polygon[2] = point(x2, y2);
  polygon[3] = point(x1, y2);
  PL(calc(cx, cy));
  return 0;
}
