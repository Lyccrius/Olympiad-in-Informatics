#include <cstdio>
#include <cmath>
#include <cstring>

const int maxN = 1e5 + 10;

long long pow2[32];

int t;
int n;
long long a[maxN];
long long b[maxN];

void Init() {
    pow2[0] = 1;
    for (int i = 1; i <= 30; i++) pow2[i] = pow2[i - 1] * 2;
    return;
}

void mian() {
    int cnt = 0;
    long long plus[maxN];
    std::memset(plus, 0, sizeof(plus));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
    for (int i = 1; i <= n; i++) {
        int p = std::ceil(std::log2(1.0 * a[i]));
        b[i] = pow2[p];
        if (b[i] != a[i]) {
            cnt++;
            plus[i] = b[i] - a[i];
        }
    }
    printf("%d\n", cnt);
    for (int i = 1; i <= n; i++) if (plus[i]) printf("%d %lld\n", i, plus[i]);
    return;
}

int main() {
    Init();
    scanf("%d", &t);
    while (t--) mian();
    return 0;
}