#include <cstdio>
#include <cmath>
#include <algorithm>

const int maxn = 1e7 + 10;

int n;
long long A[maxn];
long long C[maxn];
long long tot;
long long M;

int main() {
    while (scanf("%d", &n) != EOF) {
        tot = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%lld", &A[i]);
            tot += A[i];
        }
        M = tot / n;
        C[0] = 0;
        for (int i = 1; i < n; i++) C[i] = C[i - 1] + A[i] - M;
        std::sort(C, C + n);
        long long x1 = C[n >> 1];
        long long ans = 0;
        for (int i = 0; i < n; i++) ans += std::abs(x1 - C[i]);
        printf("%lld\n", ans);
    }
    return 0;
}