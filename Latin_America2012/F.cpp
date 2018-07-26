/// Author: Wang, Yen-Jen
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 700 + 7;

struct Dsu {
    int n;
    int cnt;
    int par[MAX_N * MAX_N];
    int sz[MAX_N * MAX_N];

    void init(int _n) {
        n = _n;
        cnt = _n;
        for (int i = 0; i < n; i++) {
            par[i] = i;
            sz[i] = 1;
        }
    }

    int find(int x) {
        if (x == par[x])
            return x;
        else
            return par[x] = find(par[x]);
    }

    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y)
            return 0;
        cnt--;
        if (sz[x] < sz[y])
            swap(x, y);
        sz[x] += sz[y];
        par[y] = x;
        return 1;
    }
} dsu;

char A[MAX_N][MAX_N];

int main() {
    int N;
    while(scanf("%d", &N) != EOF) {
        int X = N * 2;
        int Y = N * 2 + 1;
        dsu.init(X * Y);
        for (int i = 0; i < X - 1; i++)
            scanf("%s", A[i]);
        for (int i = 0; i < X; i++) {
            for (int j = 0; j < Y; j++) {
                if (j + 1 < Y) {
                if (i < X - 1 && i % 2 == j % 2 && A[i][j / 2] == 'V');
                else if (i > 0 && i % 2 != j % 2 && A[i - 1][j / 2] == 'V');
                else dsu.merge(i * Y + j, i * Y + j + 1);
                }

                if (i + 1 < X) {
                    if (j < Y - 1 && i % 2 == j % 2 && A[i][j / 2] == 'H');
                    else if (j > 0 && i % 2  != j % 2 && A[i][(j - 1) / 2] == 'H');
                    else dsu.merge(i * Y + j, (i + 1) * Y + j);
                }
            }
        }
        printf("%d\n", dsu.cnt - 1);
    }
    return 0;
}
