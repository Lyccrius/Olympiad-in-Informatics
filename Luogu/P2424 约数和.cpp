#include <cstdio>

int X, Y;

long long solve(int n) {
    long long ret = 0;
    for (long long i = 1, j, t; i <= n; i = j + 1) {
        t = n / i;
        j = n / t;
        ret += t * (j - i + 1) * (i + j) / 2;
    }
    return ret;
}

int main() {
    scanf("%d%d", &X, &Y);
    printf("%lld\n", solve(Y) - solve(X - 1));
    return 0;
}