#include <cstdio>
#include <algorithm>

int n, k;

long long solve(long long n, long long k) {
    long long ret = n * k;
    for (long long i = 1, j, t; i <= n; i = j + 1) {
        t = k / i;
        if (t) j = std::min(k / t, n);
        else j = n;
        ret -= t * (j - i + 1) * (i + j) / 2;
    }
    return ret;
}

int main() {
    scanf("%d%d", &n, &k);
    printf("%lld\n", solve(n, k));
    return 0;
}