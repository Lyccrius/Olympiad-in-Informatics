#include <cstdio>
#include <algorithm>

long long n, k;

int main() {
    scanf("%lld%lld", &n, &k);
    long long ans = n * k;
    for (long long l = 1, r; l <= n; l = r + 1) {
        if (k / l) r = std::min(k / (k / l), n);
        else r = n;
        ans -= (k / l) * (r - l + 1) * (l + r) / 2;
    }
    printf("%lld\n", ans);
    return 0;
}