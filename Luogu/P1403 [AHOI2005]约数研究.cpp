#include <cstdio>
#include <cmath>

long long n;

int mian() {
    scanf("%lld", &n);
    long long sqrtN = std::sqrt(n);
    long long ans = 0;
    for (int i = 1; i <= sqrtN; i++) ans += n / i;
    ans = ans * 2 - sqrtN * sqrtN;
    printf("%lld\n", ans);
    return;
}