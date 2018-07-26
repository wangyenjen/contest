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

const int MAX_ALPHA = 26;
const int MAX_L = 10 + 7;
const int MAX_N = 10000 + 7;

string s1 , s2;
bool vis[MAX_ALPHA];
string rd[MAX_ALPHA];
int cnt[MAX_L][MAX_N];
bool has[MAX_L][MAX_N];

inline bool check(const string &s) {
  int len = SZ(s) , now = 0;
  REP(i , len) {
    now = now<<1|(s[i] == '1');
    if(has[i + 1][now]) return 0;
  }
  return cnt[len][now] == 0;
}

inline void add(const string &s) {
  int len = SZ(s) , now = 0;
  REP(i , len) {
    now = now<<1|(s[i] == '1');
    cnt[i + 1][now]++;
  }
  has[len][now] = 1;
}

inline void del(const string &s) {
  int len = SZ(s) , now = 0;
  REP(i , len) {
    now = now<<1|(s[i] == '1');
    cnt[i + 1][now]--;
  }
  has[len][now] = 0;
}
void dfs(int ptr_s1 , int ptr_s2) {
  if (ptr_s1 == SZ(s1)) {
    if (ptr_s2 == SZ(s2)) {
      REP(i , MAX_ALPHA) {
        if (vis[i]) {
          char ss[10];
          ss[1] = 0;
          ss[0] = 'a' + i;
          PL(ss , rd[i].c_str());
        }
      }
      exit(0);
    }
    return;
  }
  if (vis[s1[ptr_s1] - 'a']) {
    int len = SZ(rd[s1[ptr_s1] - 'a']);
    if(ptr_s2 + len > SZ(s2)) return;
    REP(i , len) {
      if (s2[ptr_s2 + i] != rd[s1[ptr_s1] - 'a'][i]) return;
    }
    dfs(ptr_s1 + 1 , ptr_s2 + len);
  }
  else {
    vis[s1[ptr_s1] - 'a'] = 1;
    string &ss = rd[s1[ptr_s1] - 'a'];
    ss = "";
    for (int i = 1; i <= 10 && ptr_s2 + i <= SZ(s2); i++) {
      ss = ss + s2[ptr_s2 + i - 1];
      if (check(ss)) {
        add(ss);
        dfs(ptr_s1 + 1 , ptr_s2 + i);
        del(ss);
      }
    }
    vis[s1[ptr_s1] - 'a'] = 0;
  }
}
int main() {
  freopen("prefix.in" , "r" , stdin);
  freopen("prefix.out" , "w" , stdout);
  cin >> s1 >> s2;
  dfs(0, 0);
  return 0;
}
