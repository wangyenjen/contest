/// Author: Wang, Yen-Jen
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 50000 + 7;

struct Treap {
    Treap *lc, *rc;
    char ch;
    int sz;

    Treap(char _ch = 0) : lc(0), rc(0), ch(_ch), sz(1) {}
};

inline int my_rand() {
    static int x = 880301;
    return x = (x * 0xdefacedll + 1) % 0x7fffffff;
}

inline int get_sz(Treap *o) {
    return o ? o->sz : 0;
}

inline void pull(Treap *o) {
    o->sz = get_sz(o->lc) + 1 + get_sz(o->rc);
}

Treap* merge(Treap *a, Treap *b) {
    if(!a || !b) return a ? a : b;
    if(my_rand() % (get_sz(a) + get_sz(b)) < get_sz(a)) {
        a = new Treap(*a);
        a->rc = merge(a->rc, b);
        pull(a);
        return a;
    }
    else {
        b = new Treap(*b);
        b->lc = merge(a, b->lc);
        pull(b);
        return b;
    }
}

void split(Treap *o, int k, Treap *&a, Treap *&b) {
    if(!o) {
        a = b = 0;
        return;
    }
    if(get_sz(o->lc) + 1 <= k) {
        a = new Treap(*o);
        split(o->rc, k - (get_sz(o->lc) + 1), a->rc, b);
        pull(a);
    }
    else {
        b = new Treap(*o);
        split(o->lc, k, a, b->lc);
        pull(b);
    }
}

int cc;
Treap *rt[MAX_N];
int vnow;

void print_tr(Treap *o) {
    if(!o) return;
    if(o->lc) print_tr(o->lc);
    cout << o->ch;
    if(o->ch == 'c') cc++;
    if(o->rc) print_tr(o->rc);
}

int main() {
    rt[0] = 0;
    vnow = 0;
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    while(n--) {
        int op;
        cin >> op;
        if(op == 1) {
            int p;
            string s;
            cin >> p >> s;
            p -= cc;
            Treap *a = 0, *b = 0;
            split(rt[vnow], p, a, b);
            vnow++;
            rt[vnow] = a;
            for(char ch : s) rt[vnow] = merge(rt[vnow], new Treap(ch));
            rt[vnow] = merge(rt[vnow], b);
        }
        else if(op == 2) {
            int p, c;
            cin >> p >> c;
            p -= cc;
            c -= cc;
            Treap *x = 0, *y = 0, *z = 0;
            split(rt[vnow], p - 1, x, y);
            split(y, c, y, z);
            vnow++;
            rt[vnow] = merge(x, z);
        }
        else {
            int v , p, c;
            cin >> v >> p >> c;
            v -= cc;
            p -= cc;
            c -= cc;
            Treap *x = 0, *y = 0, *z = 0;
            split(rt[v], p - 1, x , y);
            split(y, c, y, z);
            print_tr(y);
            cout << '\n';
            rt[v] = merge(x, merge(y, z));
        }
    }
    return 0;
}
