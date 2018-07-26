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

#define x first
#define y second

set<pii> st;
map<pii,int> dp , id;
map<pii,pii> path , path2;
map<int,vector<pii> > s_y;
unordered_map<int,pii> last1 , last2 , last3;
vector<pii> v;

void print_path(pii u) {
	if(u == MP(0 , 0)) return;
	if(path[u].y == u.y) {
		int p = lower_bound(ALL(s_y[u.y]) , path[u]) - s_y[u.y].begin();
		int p2 = lower_bound(ALL(s_y[u.y]) , u) - s_y[u.y].begin();
		print_path(path2[path[u]]);
		if(p < p2) {
			for(int i = p; i >= 0; i--) printf("%d ",id[s_y[u.y][i]]);
			REP1(i , p + 1 , p2 - 1) printf("%d ",id[s_y[u.y][i]]);
		}
		else {
			REP1(i , p , SZ(s_y[u.y]) - 1) printf("%d ",id[s_y[u.y][i]]);
			for(int i = p - 1; i > p2; i--) printf("%d ",id[s_y[u.y][i]]);
		}
	}
	else print_path(path[u]);
	printf("%d ",id[u]);
}

int main() {
  freopen("queen.in" , "r" , stdin);
  freopen("queen.out" , "w" , stdout);
  int n;
  RI(n);
  v.PB(MP(0 , 0));
  dp[MP(0 , 0)] = 0;
  path[MP(0 , 0)] = MP(-1 , -1);
  last1[0] = MP(0 , 0);
  last2[0] = MP(0 , 0);
  last3[0] = MP(0 , 0);
  REP1(i , 1 , n) {
    int x , y;
    RI(x , y);
    v.PB(MP(x , y));
    s_y[y].PB(MP(x , y));
    id[MP(x , y)] = i;
  }
  int ans = 0;
  for(auto &iter : s_y) {
    vector<pii> &t = iter.y;
    sort(ALL(t));
    st.clear();
    REP(i , SZ(t)) {
      pii &p = t[i];
      pii tmp = pii(-1 , -1);
      if(last1.count(p.x) && (tmp == MP(-1 , -1) || dp[last1[p.x]] > dp[tmp])) {
          tmp = last1[p.x];
      }
      if(last2.count(p.x-p.y) && (tmp == MP(-1 , -1) || dp[last2[p.x-p.y]] > dp[tmp])) {
          tmp = last2[p.x-p.y];
      }
      if(last3.count(p.x+p.y) && (tmp == MP(-1 , -1) || dp[last3[p.x+p.y]] > dp[tmp])) {
          tmp = last3[p.x+p.y];
      }
      dp[p] = -1;
      if(SZ(st)) {
        if(dp[p] < (*prev(st.end())).x + i + 1) {
            dp[p] = (*prev(st.end())).x + i + 1;
            path[p] = t[(*prev(st.end())).y];
        }
      }
      if(tmp != pii(-1 , -1) && dp[tmp] != -1) {
        st.insert(MP(dp[tmp] , i));
        path2[p] = tmp;
        if(dp[p] < dp[tmp]+1) {
            dp[p] = dp[tmp] + 1;
            path[p] = tmp;
        }
      }
    }
    st.clear();
    for(int i = SZ(t) - 1; i >= 0; i--) {
      pii &p = t[i];
      pii tmp = MP(-1 , -1);
      if(last1.count(p.x) && (tmp == MP(-1 , -1) || dp[last1[p.x]] > dp[tmp])) {
          tmp = last1[p.x];
      }
      if(last2.count(p.x-p.y) && (tmp == MP(-1 , -1) || dp[last2[p.x-p.y]] > dp[tmp])) {
          tmp = last2[p.x-p.y];
      }
      if(last3.count(p.x+p.y) && (tmp == MP(-1 , -1) || dp[last3[p.x+p.y]] > dp[tmp])) {
          tmp = last3[p.x+p.y];
      }
      if(SZ(st)) {
        if(dp[p] < (*prev(st.end())).x + (SZ(t) - i)) {
            dp[p] = (*prev(st.end())).x + (SZ(t) - i);
            path[p] = t[(*prev(st.end())).y];
        }
      }
      if(tmp != MP(-1 , -1) && dp[tmp] != -1) {
        st.insert(pii(dp[tmp] , i));
        if(dp[p] < dp[tmp] + 1) {
          dp[p] = dp[tmp] + 1;
          path[p] = tmp;
        }
      }
      ans = max(ans , dp[p]);
    }
    for(pii &p : t) {
      last1[p.x] = p;
      last2[p.x-p.y] = p;
      last3[p.x+p.y] = p;
    }
  }
  PL(ans);
  REP1(i , 1 , n) {
    if(dp[v[i]] == ans) {
      print_path(v[i]);
      PL();
      break;
    }
  }
  return 0;
}
