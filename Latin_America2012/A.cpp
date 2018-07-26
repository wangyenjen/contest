/// Author: Wang, Yen-Jen
#include <bits/stdc++.h>

using namespace std;

constexpr long inf = 2000000000000000L;

int x[1000], w[1000];
long dp[1001][1001];
long sw[1001], swx[1001];

void dfs(int k, int l, int r, int lb, int rb) {
    if (l > r)
        return;
    int m = (l + r) / 2;
    int best = lb;
    for (int i = lb; i <= min(rb, m - 1); i++) {
        long val = dp[k - 1][i] + swx[i] - sw[i] * x[m - 1] + sw[m] * x[m - 1] - swx[m];
        if (dp[k][m] > val) {
            dp[k][m] = val;
            best = i;
        }
    }
    dfs(k, l, m - 1, lb, best);
    dfs(k, m + 1, r, best, rb);
}

long solve(int n, int k) {
    for (int i = 0; i < n; i++)
        scanf("%d %d", x + i, w + i);
    for (int i = 0; i < n; i++) {
        sw[i + 1] = sw[i] + w[i];
        swx[i + 1] = swx[i] + (long) w[i] * x[i];
    }
    fill_n(dp[0] + 1, n, inf);
    for (int j = 1; j <= k; j++) {
        for (int i = 1; i <= n; i++) {
            dp[j][i] = inf;
        }
    }
    for (int i = 1; i <= k; i++) {
        dfs(i, 1, n, 0, n - 1);
    }
    return dp[k][n];
}

int main() {
    int n, k;
    while(scanf("%d %d", &n, &k) == 2)
        printf("%ld\n", solve(n, k));
}
