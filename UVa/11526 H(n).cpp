#include <cstdio>
#include <cmath>

int T;

long long n;

void mian() {
    scanf("%lld", &n);
    long long sqrtN = std::sqrt(n);
    long long ans = 0;
    for (int i = 1; i <= sqrtN; i++) ans += n / i;
    ans = ans * 2 - sqrtN * sqrtN;
    printf("%lld\n", ans);
    return;
}

int main() {
    scanf("%d", &T);
    while (T--) mian();
    return 0;
}