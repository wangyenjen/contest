/// Author: Wang, Yen-Jen
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 100000 + 7;
const int MAX_L = 1000000 + 7;

struct Node {
  static Node mem[MAX_L], *pmem;
  Node *ch[26];
  int nxt_cnt, sz;
  bool has_end;

  Node() : nxt_cnt(0), sz(0), has_end(0) {
    memset(ch, 0, sizeof(ch));
  }
} Node::mem[MAX_L], *Node::pmem = Node::mem;

Node *root;

void init() {
  Node::pmem = Node::mem;
  root = new (Node::pmem++)Node();
}

void insert(string &s) {
  Node *p = root;
  p->sz++;
  for (char c : s) {
    int x = c - 'a';
    if (!p->ch[x]) {
      p->ch[x] = new (Node::pmem++)Node();
      p->nxt_cnt++;
    }
    p = p->ch[x];
    p->sz++;
  }
  p->has_end = 1;
}

ll calc(Node *o) {
  if (o->nxt_cnt == 0) return 0;
  else if (o->nxt_cnt == 1) {
    ll tmp = (o == root) * o->sz;
    if (o->has_end) tmp = o->sz - 1;
    for (int i = 0; i < 26; i++)
      if (o->ch[i]) return calc(o->ch[i]) + tmp;
  }
  else {
    ll res = o->sz - o->has_end;
    for (int i = 0; i < 26; i++)
      if (o->ch[i]) res += calc(o->ch[i]);
    return res;
  }
  __builtin_unreachable();
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int N;
  while (cin >> N) {
    init();
    for (int i = 0; i < N; i++) {
      string s;
      cin >> s;
      insert(s);
    }
    double ans = 1. * calc(root) / N;
    printf("%.2f\n", ans);
  }
  return 0;
}
