#include <cstdio>

long long a1, a2, n;

int main() {
    scanf("%lld%lld%lld", &a1, &a2, &n);
    long long d = a2 - a1;
    long long ans = (a1 + a1 + (n - 1) * d) * n / 2;
    printf("%lld\n", ans);
    return 0;
}