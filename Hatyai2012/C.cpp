/// Author: Wang, Yen-Jen
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 10000 + 7;

double calc(int n, double sx, double sy, double sxx, double syy, double sxy) {
    double a = n * sxy - sx * sy;
    double b = n * (syy - sxx) - (sy * sy - sx * sx);
    double t = atan2(-2 * a, b) / 2;
    double c = cos(t), s = sin(t);
    return (sxx * c * c + syy * s * s + 2 * sxy * c * s -
            (sx * sx * c * c + sy * sy * s * s + 2 * sx * sy * c * s) / n) / n;
}

double ax[MAX_N], ay[MAX_N];

int main() {
    for (int kcase = 1; ; kcase++) {
        int n, q;
        scanf("%d %d", &n, &q);
        if (n == 0) break;
        printf("Case %d:\n", kcase);
        double sx = 0, sy = 0, sxx = 0, syy = 0, sxy = 0;
        for (int i = 0; i < n; i++) {
            double x, y;
            scanf("%lf %lf", &x, &y);
            ax[i] = x;
            ay[i] = y;
            sx += x;
            sy += y;
            sxx += x * x;
            syy += y * y;
            sxy += x * y;
        }
        printf("%.5f\n", calc(n, sx, sy, sxx, syy, sxy));
        for (int i = 1; i <= q; i++) {
            int s, m;
            scanf("%d %d", &s, &m);
            double x = ax[s], y = ay[s];
            m--;
            printf("%d: %.5f\n", i, calc(n + m, sx + m * x, sy + m * y, sxx + m * x * x, syy + m * y * y, sxy + m * x * y));
        }
    }
}
