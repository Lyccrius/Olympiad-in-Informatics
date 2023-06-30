#include <iostream>
#include <algorithm>

const int maxN = 2000;
const int mod = 1e9 + 9;

int n, k;
int a[maxN + 10];
int b[maxN + 10];
int r[maxN + 10];
int f[maxN + 10][maxN + 10];
int g[maxN + 10];
int fac[maxN + 10];
int inv[maxN + 10];
int ans[maxN + 10];

int C(int n, int m) {
    return 1ll * fac[n] * inv[m] % mod * inv[n - m] % mod;
}

int main() {
    std::cin >> n >> k;
    if ((n + k) & 1) {std::cout << 0 << '\n'; return 0;}
    k = (n + k) / 2;
    fac[0] = 1;
    for (int i = 1; i <= n; i++) fac[i] = 1ll * fac[i - 1] * i % mod;
    inv[1] = 1;
    for (int i = 2; i <= n; i++) inv[i] = 1ll * inv[mod % i] * (mod - mod / i) % mod;
    for (int i = 2; i <= n; i++) inv[i] = 1ll * inv[i - 1] * inv[i] % mod;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) std::cin >> b[i];
    std::sort(a + 1, a + n + 1);
    std::sort(b + 1, b + n + 1);
    for (int i = 1; i <= n; i++) {
        r[i] = r[i - 1];
        while (r[i] < n && b[r[i] + 1] < a[i]) r[i]++;
    }
    f[0][0] = 1;
    for (int i = 1; i <= n; i++) for (int j = 0; j <= i; j++) f[i][j] = (1ll * f[i - 1][j] + 1ll * (r[i] - j + 1) * f[i - 1][j - 1] % mod) % mod;
    for (int i = 0; i <= n; i++) g[i] = 1ll * f[n][i] * fac[n - i] % mod;
    for (int i = n; i >= k; i--) {
        ans[i] = g[i];
        for (int j = i + 1; j <= n; j++) ans[i] = (ans[i] - 1ll * ans[j] * C(j, i) % mod + mod) % mod;
    }
    std::cout << ans[k] << '\n';
    return 0;
}