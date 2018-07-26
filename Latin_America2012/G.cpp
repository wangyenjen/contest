/// Author: Wang, Yen-Jen
#include <bits/stdc++.h>

using namespace std;

const int MAX_R = 50 + 7;
const int MAX_C = 50 + 7;
const int MAX_N = 50 * 50 + 7;
const int INF = 0x3f3f3f3f;

struct Edge {
    int u, v, cap, flow;

    Edge(int _u = 0, int _v = 0, int _cap = 0, int _flow = 0) : u(_u), v(_v), cap(_cap), flow(_flow) {}
};

int N, M;
vector<int> G[MAX_N];
vector<Edge> edges;
int d[MAX_N], cur[MAX_N];

void init(int n) {
    N = n;
    M = 0;
    edges.clear();
    for (int i = 0; i < N; i++)
        G[i].clear();
}

void add_edge(int u, int v, int cap) {
    edges.push_back(Edge(u, v, cap, 0));
    edges.push_back(Edge(v, u, 0, 0));
    M = (int)edges.size();
    G[u].push_back(M - 2);
    G[v].push_back(M - 1);
}

bool bfs(int st, int ed) {
    static bool vis[MAX_N];
    queue<int> que;
    for (int i = 0; i < N; i++) {
        vis[i] = 0;
        d[i] = -1;
    }
    d[st] = 0;
    vis[st] = 1;
    que.push(st);
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        for (int id : G[u]) {
            Edge &e = edges[id];
            if (!vis[e.v] && e.cap > e.flow) {
                vis[e.v] = 1;
                d[e.v] = d[u] + 1;
                que.push(e.v);
            }
        }
    }
    return vis[ed];
}

int dfs(int u, int ed, int r) {
    if (u == ed || r == 0)
        return r;
    int res = 0;
    for (int &i = cur[u]; i < (int)G[u].size(); i++) {
        Edge &e = edges[G[u][i]];
        int f = 0;
        if (d[e.v] == d[u] + 1 && (f = dfs(e.v, ed, min(r, e.cap - e.flow))) > 0) {
            res += f;
            r -= f;
            edges[G[u][i] ^ 1].flow -= f;
            e.flow += f;
            if (r == 0)
                break;
        }
    }
    return res;
}

int max_flow(int st, int ed) {
    int res = 0;
    while (bfs(st, ed)) {
        memset(cur, 0, sizeof(int) * (N + 1));
        res += dfs(st, ed, INF);
    }
    return res;
}

char A[MAX_R][MAX_C];
int id[MAX_R][MAX_C];

int main() {
    int R, C;
    while (scanf("%d%d", &R, &C) != EOF) {
        int max_id = 0;
        for (int i = 0; i < R; i++) {
            scanf("%s", A[i]);
            for (int j = 0; j < C; j++) {
                id[i][j] = -1;
                if (A[i][j] == '.')
                    id[i][j] = max_id++;
            }
        }
        if (max_id % 2 == 1) {
            puts("1");
            continue;
        }
        int st = max_id++;
        int ed = max_id++;
        init(max_id);
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                if (A[i][j] == 'X')
                    continue;
                if ((i + j) & 1) {
                    add_edge(id[i][j], ed, 1);
                }
                else {
                    add_edge(st, id[i][j], 1);
                    if (i - 1 >= 0 && A[i - 1][j] != 'X')
                        add_edge(id[i][j], id[i - 1][j], 1);
                    if (i + 1 < R && A[i + 1][j] != 'X')
                        add_edge(id[i][j], id[i + 1][j], 1);
                    if (j - 1 >= 0 && A[i][j - 1] != 'X')
                        add_edge(id[i][j], id[i][j - 1], 1);
                    if (j + 1 < C && A[i][j + 1] != 'X')
                        add_edge(id[i][j], id[i][j + 1], 1);
                }
            }
        }
        if (max_flow(st, ed) == (max_id - 2) / 2) {
            puts("2");
        }
        else puts("1");
    }
    return 0;
}
