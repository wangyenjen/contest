/// Author: Wang, Yen-Jen
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 100000 + 7;

struct Dsu {
    int n;
    int par[MAX_N];
    int sz[MAX_N];

    void init(int _n) {
        n = _n;
        for (int i = 1; i <= n; i++) {
            par[i] = i;
            sz[i] = 1;
        }
    }

    int find(int x) {
        if (par[x] == x)
            return x;
        else
            return par[x] = find(par[x]);
    }

    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y)
            return 0;
        if (sz[x] < sz[y])
            swap(x, y);
        sz[x] += sz[y];
        par[y] = x;
        return 1;
    }

    bool query(int x, int y) {
        x = find(x);
        y = find(y);
        return x == y;
    }
} dsu;

int anc[MAX_N][20];
int dp3[MAX_N];
bool vis2[MAX_N];
int dp[MAX_N];
int dp2[MAX_N];
bool vis[MAX_N];
int path[MAX_N];
int cyc_len[MAX_N];
bool on_cyc[MAX_N];
int nxt[MAX_N];

void dfs(int u) {
    vis2[u] = 1;
    if (vis2[nxt[u]]) {
        int v = u;
        cyc_len[dsu.find(u)] = dp2[u] + 1 - dp2[nxt[u]];
        while (1) {
            on_cyc[v] = 1;
            if (v == nxt[u])
                break;
            v = path[v];
        }
    }
    else {
        path[nxt[u]] = u;
        dp2[nxt[u]] = dp2[u] + 1;
        dfs(nxt[u]);
    }
}

void dfs2(int u) {
    if (vis[u])
        return;
    vis[u] = 1;
    if (on_cyc[u]) {
        dp[u] = 0;
        dp3[u] = dp2[u];
    }
    else {
        dfs2(nxt[u]);
        dp[u] = dp[nxt[u]] + 1;
        dp3[u] = dp3[nxt[u]];
    }
}

int main() {
    int N;
    while (scanf("%d", &N) != EOF) {
        dsu.init(N);
        for (int i = 1; i <= N; i++) {
            scanf("%d", &nxt[i]);
            dsu.merge(i, nxt[i]);
            anc[i][0] = nxt[i];
            vis[i] = 0;
            vis2[i] = 0;
            dp[i] = 0;
            dp2[i] = 0;
            dp3[i] = 0;
            on_cyc[i] = 0;
            path[i] = 0;
        }
        for (int i = 1; i < 20; i++) {
            for (int u = 1; u <= N; u++)
            anc[u][i] = anc[anc[u][i - 1]][i - 1];
        }
        for (int i = 1; i <= N; i++) {
            if (vis[dsu.find(i)])
                continue;
            vis[dsu.find(i)] = 1;
            dp2[i] = 1;
            dfs(i);
        }
        for (int i = 1; i <= N; i++) vis[i] = 0;
        for (int i = 1; i <= N; i++) {
            dfs2(i);
        }
        int Q;
        scanf("%d", &Q);
        while (Q--) {
            int x, y;
            scanf("%d%d", &x, &y);
            if (dsu.query(x, y) == 0)
                puts("-1");
            else {
                int a = dp3[x];
                int b = dp3[y];
                if (a > b) swap(a, b);
                int ans;
                if (a == b) {
                    if (dp[x] < dp[y])
                        swap(x, y);
                    a = x, b = y;
                    for (int i = 19; i >= 0; i--) {
                        if ((dp[a] - dp[b]) & (1<<i)) {
                            a = anc[a][i];
                        }
                    }
                    if (a != b) {
                        for (int i = 19; i >= 0; i--) {
                            if (anc[a][i] != anc[b][i]) {
                                a = anc[a][i];
                                b = anc[b][i];
                            }
                        }
                        if (a != b) {
                            a = anc[a][0];
                            b = anc[b][0];
                        }
                    }
                    ans = dp[x] + dp[y] - 2 * dp[a];
                }
                else ans = dp[x] + dp[y] + min(b - a, cyc_len[dsu.find(x)] - (b - a));
                printf("%d\n", ans);
            }
        }
    }
    return 0;
}
