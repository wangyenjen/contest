// Author: Yen-Jen Wang
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 200000 + 7;

int my_rand() {
  static int x = 880301;
  return x = (x * 0xdefacedll + 1) % 0x7fffffff;
}

struct Treap {
  static Treap mem[MAX_N], *pmem;
  Treap *lc, *rc;
  pair<int, int> val;
  int sz;

  Treap() {}
  Treap(pair<int, int> _val) : lc(0), rc(0), val(_val), sz(1) {}
} Treap::mem[MAX_N], *Treap::pmem = Treap::mem;

int get_sz(Treap *o) {
  return o ? o->sz : 0;
}

void pull(Treap *o) {
  o->sz = get_sz(o->lc) + 1 + get_sz(o->rc);
}

Treap* merge(Treap *a, Treap *b) {
  if (!a || !b) return a ? a : b;
  else if (my_rand() % (get_sz(a) + get_sz(b)) < get_sz(a)) {
    a->rc = merge(a->rc, b);
    pull(a);
    return a;
  }
  else {
    b->lc = merge(a, b->lc);
    pull(b);
    return b;
  }
}

void split(Treap *o, pair<int, int> val, Treap *&a, Treap *&b) {
  if (!o) a = b = 0;
  else if (o->val <= val) {
    a = o;
    split(o->rc, val, a->rc, b);
    pull(a);
  }
  else {
    b = o;
    split(o->lc, val, a, b->lc);
    pull(b);
  }
}

pair<int, int> find_kth(Treap *o, int k) {
  if (get_sz(o->lc) + 1 == k) return o->val;
  else if (get_sz(o->lc) + 1 > k) return find_kth(o->lc, k);
  else return find_kth(o->rc, k - (get_sz(o->lc) + 1));
}

void print_tr2(Treap *o) {
  if (!o) return;
  if (o->lc) print_tr2(o->lc);
  printf(" (%d, %d) ", o->val.first, o->val.second);
  if (o->rc) print_tr2(o->rc);
}

void print_tr(Treap *o) {
  printf("{");
  print_tr2(o);
  puts("}");
}

void ins(Treap *&o, pair<int, int> val) {
  Treap *a = 0, *b = 0;
  split(o, val, a, b);
  o = merge(merge(a, new (Treap::pmem++)Treap(val)), b);
}

void del(Treap *&o, pair<int, int> val) {
  Treap *a = 0, *b = 0, *c = 0;
  split(o, make_pair(val.first, val.second - 1), a, b);
  split(b, val, b, c);
  o = merge(a, c);
}

struct Dsu {
  int par[MAX_N], sz[MAX_N], mn[MAX_N];

  void init(int n) {
    for (int i = 0; i < n; i++) {
      par[i] = i;
      sz[i] = 1;
      mn[i] = i;
    }
  }

  int find(int x) {
    if (par[x] == x) return x;
    else return par[x] = find(par[x]);
  }

  bool merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return 0;
    if (sz[x] < sz[y]) swap(x, y);
    sz[x] += sz[y];
    mn[x] = min(mn[x], mn[y]);
    par[y] = x;
    return 1;
  }

  bool query(int x, int y) {
    return find(x) == find(y);
  }

  int get_mn(int x) {
    return mn[find(x)];
  }
} dsu;

char str[MAX_N];
int sa[MAX_N] , cnt[MAX_N] , rk[2][MAX_N] , ht[MAX_N];

void build_sa(int n , int m) {
    int *x = rk[0];
    int *y = rk[1];
    for(int i = 0; i < m; i++) cnt[i] = 0;
    for(int i = 0; i <= n; i++) cnt[x[i] = str[i]]++;
    for(int i = 1; i < m; i++) cnt[i] += cnt[i - 1];
    for(int i = n; i >= 0; i--) sa[--cnt[x[i]]] = i;
    for(int k = 1; ; k <<= 1) {
        int p = 0;
        for(int i = n - k + 1; i <= n; i++) y[p++] = i;
        for(int i = 0; i <= n; i++) if(sa[i] >= k) y[p++] = sa[i] - k;
        for(int i = 0; i < m; i++) cnt[i] = 0;
        for(int i = 0; i <= n; i++) cnt[x[y[i]]]++;
        for(int i = 1; i < m; i++) cnt[i] += cnt[i - 1];
        for(int i = n; i >= 0; i--) sa[--cnt[x[y[i]]]] = y[i];
        swap(x , y);
        p = 1;
        x[sa[0]] = 0;
        for(int i = 1; i <= n; i++) x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k] ? p - 1 : p++);
        if(p >= n + 1) break;
        else m = p;
    }
}

void build_ht(int n) {
    int *x = rk[0];
    for(int i = 1; i <= n; i++) x[sa[i]] = i;
    for(int i = 0 , h = 0; i < n; i++) {
        int j = sa[x[i] - 1];
        if(h) h--;
        while(str[i + h] == str[j + h]) h++;
        ht[x[i]] = h;
    }
}

int ans[MAX_N];
vector<int> vhs[MAX_N];
vector<pair<int, int> > vqs[MAX_N];

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%s", str);
    int n = strlen(str);
    for (int i = 0; i <= n; i++) vhs[i].clear();
    build_sa(n, 128);
    build_ht(n);
    for (int i = 2; i <= n; i++) vhs[ht[i]].push_back(i);
    dsu.init(n);
    int q;
    scanf("%d", &q);
    for (int i = 1; i <= n; i++) vqs[i].clear();
    for (int i = 0; i < q; i++) {
      int k, m;
      scanf("%d%d", &k, &m);
      vqs[k].emplace_back(m, i);
      ans[i] = -1;
    }
    Treap::pmem = Treap::mem;
    Treap *tr = 0;
    for (int i = n; i >= 1; i--) {
      int *x = rk[0];
      ins(tr, make_pair(x[n - i], n - i));
      for (int id: vhs[i]) {
        int a = sa[id - 1];
        int b = sa[id];
        if (!dsu.query(a, b)) {
          del(tr, make_pair(x[dsu.find(a)], dsu.get_mn(a)));
          del(tr, make_pair(x[dsu.find(b)], dsu.get_mn(b)));
          dsu.merge(a, b);
          ins(tr, make_pair(x[dsu.find(a)], dsu.get_mn(a)));
        }
      }
      for (pair<int, int> p: vqs[i]) {
        int m, id;
        tie(m, id) = p;
        if (m <= get_sz(tr)) ans[id] = find_kth(tr, m).second;
      }
    }
    for (int i = 0; i < q; i++) {
      if (ans[i] == -1) puts("Not found");
      else printf("%d\n", ans[i]);
    }
  }
  return 0;
}
