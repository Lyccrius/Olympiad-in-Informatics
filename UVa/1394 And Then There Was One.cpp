#include <cstdio>

const int maxN = 10000 + 10;

int n, k, m;
int f[maxN];

int main() {
    while (scanf("%d%d%d", &n, &k, &m) == 3 && n) {
        f[1] = 0;
        for (int i = 2; i <= n; i++) f[i] = (f[i - 1] + k) % i;
        int ans = (m - k + 1 + f[n]) % n;
        if (ans <= 0) ans += n;
        printf("%d\n", ans);
    }
    return 0;
}