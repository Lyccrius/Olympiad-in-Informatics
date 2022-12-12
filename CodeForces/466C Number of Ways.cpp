#include <cstdio>

const int maxN = 5e5 + 10;

int n;
long long a[maxN];
long long p[maxN];
long long cnt;
long long res;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%lld", &a[i]), p[i] = p[i - 1] + a[i];
    if (p[n] % 3) {
        printf("%d\n", 0);
        return 0;
    }
    for (int i = 2; i < n; i++) {
        if (p[i - 1] * 3 == p[n]) cnt++;
        if (p[i] * 3 == p[n] * 2) res += cnt;
    }
    printf("%lld\n", res);
    return 0;
}