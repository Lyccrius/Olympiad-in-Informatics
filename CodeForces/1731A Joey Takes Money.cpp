#include <cstdio>
#include <algorithm>

const int maxN = 50 + 10;

int t;
int n;
long long a[maxN];

void mian() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
    std::sort(a + 1, a + n + 1);
    for (int i = 1; i < n; i++) {
        a[i + 1] = a[i] * a[i + 1];
        a[i] = 1;
    }
    printf("%lld\n", (a[n] + n - 1) * 2022);
    return;
}

int main() {
    scanf("%d", &t);
    while (t--) mian();
    return 0;
}