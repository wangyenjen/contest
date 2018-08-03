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

bool query(int a, int b) {
	cout << "? " << (char)('A' + a) << ' ' << (char)('A' + b) << endl;
	string s;
	cin >> s;
	return s == "<";
}

void answer(vector<int> ans) {
	cout << "! ";
	for (int x : ans)
		cout << (char)('A' + x);
	cout << endl;
}

// for subtask 3 - N = 5, Q = 7
const int N_SUBTASK_3 = 5;

bool vis[N_SUBTASK_3];
vector<pii> decs;
vector<vector<int> > perms;

void build_perms(vector<int> v) {
  if (SZ(v) == N_SUBTASK_3) perms.PB(v);
  else {
    REP(i, N_SUBTASK_3) {
      if (vis[i]) continue;
      vis[i] = 1;
      v.PB(i);
      build_perms(v);
      v.pop_back();
      vis[i] = 0;
    }
  }
}

pii dfs(vector<int> ps) {
  if (SZ(ps) == 1) return MP(0, -1);
  int mn = INF, best = -1;
  REP(i, SZ(decs)) {
    vector<int> nps[2];
    for (int id : ps) {
      vector<int> v;
      REP(j, N_SUBTASK_3) {
        if (perms[id][j] == decs[i].F || perms[id][j] == decs[i].S) v.PB(perms[id][j]);
      }
      nps[v[0] < v[1]].PB(id);
    }
    if (SZ(nps[0]) == 0 || SZ(nps[1]) == 0 || abs(SZ(nps[0]) - SZ(nps[1])) > 1) continue;
    pii p0 = dfs(nps[0]);
    pii p1 = dfs(nps[1]);
    if (max(p0.F, p1.F) + 1 < mn) {
      mn = max(p0.F, p1.F) + 1;
      best = i;
    }
  }
  return MP(mn, best);
}

int main() {
  int N, Q;
  RI(N, Q);
  if (N == 26) {
    vector<int> vs;
    REP(i, N) {
      int p = lower_bound(ALL(vs), i, query) - vs.begin();
      vs.PB(i);
      for (int i = SZ(vs) - 1; i > p; i--) swap(vs[i], vs[i - 1]);
    }
    answer(vs);
  }
  else {
    build_perms(vector<int> ());
    REP(i, N_SUBTASK_3) {
      REP(j, i) decs.PB(MP(j, i));
    }
    vector<int> ps;
    REP(i, SZ(perms)) ps.PB(i);
    while (SZ(ps) > 1) {
      int id = dfs(ps).S;
      bool res = query(decs[id].F, decs[id].S);
      vector<int> nps;
      for (int i : ps) {
        vector<int> v;
        REP(j, N_SUBTASK_3) {
          if (perms[i][j] == decs[id].F || perms[i][j] == decs[id].S) v.PB(perms[i][j]);
        }
        if ((v[0] < v[1]) == res) nps.PB(i);
      }
      ps = nps;
    }
    answer(perms[ps[0]]);
  }
  return 0;
}

