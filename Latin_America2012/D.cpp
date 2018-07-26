/// Author: Wang, Yen-Jen
#include <bits/stdc++.h>

using namespace std;

int cnt[10];

int main() {
    int n, m;
    while(scanf("%d%d", &n, &m) != EOF) {
    int ans = 0;
    for (int i = n; i <= m; i++) {
        memset(cnt, 0, sizeof(cnt));
        int j = i;
        while (j) {
            cnt[j % 10]++;
            j /= 10;
        }
        bool check = 1;
        for (j = 0; j < 10; j++) {
            if (cnt[j] > 1)
                check = 0;
        }
        if (check)
            ans++;
    }
    printf("%d\n", ans);
    }
    return 0;
}
