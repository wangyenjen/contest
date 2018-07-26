/// Author: Wang, Yen-Jen
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 100000 + 7;

struct Bit {
    int N;
    int tr[MAX_N];

    void init(int n) {
        N = n;
        for (int i = 0; i <= N; i++)
            tr[i] = 0;
    }

    void add(int p, int x) {
        for (int i = p; i <= N; i += i & -i)
            tr[i] += x;
    }

    int query(int p) {
        int t = 0;
        for (int i = p; i > 0; i -= i & -i)
            t += tr[i];
        return t;
    }

    int query(int l, int r) {
        return query(r) - query(l - 1);
    }
} tr1, tr2;

int A[MAX_N];

int main() {
    int N, K;
    while (scanf("%d%d", &N, &K) != EOF) {
        tr1.init(N);
        tr2.init(N);
        for (int i = 1; i <= N; i++) {
            int x;
            scanf("%d", &x);
            if (x < 0)
                A[i] = -1;
            else if (x == 0)
                A[i] = 0;
            else
                A[i] = 1;
            if (A[i] < 0)
                tr1.add(i, 1);
            else if (A[i] == 0)
                tr2.add(i, 1);
        }
        while (K--) {
            char op[10];
            int a, b;
            scanf("%s%d%d", op, &a, &b);
            if (op[0] == 'C') {
                if (A[a] < 0)
                    tr1.add(a, -1);
                else if (A[a] == 0)
                    tr2.add(a, -1);
                if (b < 0)
                    A[a] = -1;
                else if (b == 0)
                    A[a] = 0;
                else
                    A[a] = 1;
                if (A[a] == 0)
                    tr2.add(a, 1);
                else if (A[a] < 0)
                    tr1.add(a, 1);
            }
            else {
                if (tr2.query(a, b))
                    putchar('0');
                else if (tr1.query(a, b) % 2 == 0)
                    putchar('+');
                else
                    putchar('-');
            }
        }
        putchar('\n');
    }
    return 0;
}
