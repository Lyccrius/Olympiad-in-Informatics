#include <iostream>

typedef long long lxl;

const int maxN = 1e7;
const int maxK = 5;
const int mod = 998244353;

int n, x, y, m, k;
int a[maxN + 10];
int b[maxN + 10];
lxl c[maxN + 10];
int f[maxK + 10];
lxl ans;

signed main() {
    std::cin >> n >> a[1] >> x >> y >> m >> k;
    for (int i = 2; i <= n; i++) a[i] = (1ll * a[i - 1] * x + y) % m;
    for (int i = 1; i <= n; i++) {
        f[0] = (f[0] + a[i]) % mod;
        for (int j = k; j >= 1; j--) {
            f[j] = (f[j] + f[j - 1]) % mod;
        }
        b[i] = f[k];
    }
    for (int i = 1; i <= n; i++) c[i] = 1ll * b[i] * i;
    for (int i = 1; i <= n; i++) ans = ans ^ c[i];
    std::cout << ans << '\n';
    return 0;
}