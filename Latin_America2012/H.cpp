/// Author: Wang, Yen-Jen
#include <bits/stdc++.h>

using namespace std;

int main() {
    int N;
    while (scanf("%d", &N) != EOF) {
        if (N % 6 == 0)
            puts("Y");
        else
            puts("N");
    }
    return 0;
}
