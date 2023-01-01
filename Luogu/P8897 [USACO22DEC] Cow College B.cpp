#include <cstdio>
#include <algorithm>

const int maxN = 1e5 + 10;

int N;
long long c[maxN];
long long ans;
long long res;

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) scanf("%lld", &c[i]);
    std::sort(c + 1, c + N + 1);
    for (int i = 1; i <= N; i++) {
        if (ans < c[i] * (N - (std::lower_bound(c + 1, c + N + 1, c[i]) - c) + 1)) {
            ans = c[i] * (N - (std::lower_bound(c + 1, c + N + 1, c[i]) - c) + 1);
            res = c[i];
        }
    }
    printf("%lld %lld\n", ans, res);
    return 0;
}