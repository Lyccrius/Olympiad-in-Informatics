#include <cstdio>
#include <cmath>
#include <algorithm>

const int maxN = 1e5;
const int inf = 1e9;

long long n, m;
long long a[maxN + 10];

int main() {
    scanf("%lld%lld", &n, &m);
    bool dif = false;
    for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
    for (int i = 1; i <= n; i++) if (a[i] != 1) { dif = true; break; }
    if (dif == false || m == 0) {
        printf("xiaogougege\n");
        return 0;
    }
    long long l = 1;
    long long r = inf + 1;
    for (int i = 1; i <= n; i++) {
        l = std::max(l, (long long)std::ceil(1.0 * m / (i * a[i])));
        if (a[i] == 1) continue;
        r = std::min(r, (long long)std::ceil(1.0 * m / (i * (a[i] - 1))));
    }
    long long ans = std::max((long long)0, r - l);
    printf("%lld\n", ans);
    return 0;
}