#include <iostream>
#include <algorithm>

const int maxN = 1000;
const int maxX = 5000;
const int mod = 998244353;

int n, x;
int a[maxN + 10];
int c[maxX + 10];
int f[maxX + 10];
int g[maxX + 10];
int fac[maxX + 10];
int inv[maxX + 10];

int main() {
    std::cin >> n >> x;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    std::sort(a + 1, a + n + 1);
    fac[0] = 1;
    for (int i = 1; i <= n; i++) fac[i] = 1ll * fac[i - 1] * i % mod;
    inv[1] = 1;
    for (int i = 2; i <= n; i++) inv[i] = 1ll * inv[mod % i] * (mod - mod / i) % mod;
    inv[0] = 1;
    for (int i = 1; i <= n; i++) inv[i] = 1ll * inv[i - 1] * inv[i] % mod;
    for (int i = 1; i <= n; i++) c[a[i]]++;
    for (int i = 1; i <= x; i++) c[i] += c[i - 1];
    for (int j = 0; j <= x; j++) {
        if (c[j] == 0) {
            f[j] = j;
            g[j] = 1;
        } else {
            f[j] = 0;
            g[j] = 0;
            for (int i = 1; i <= c[j]; i++) if (f[j] <= f[j % a[i]]) f[j] = f[j % a[i]];
            for (int i = 1; i <= c[j]; i++) if (f[j] == f[j % a[i]]) g[j] = (g[j] + 1ll * g[j % a[i]] * fac[c[j] - 1] % mod * inv[c[j % a[i]]] % mod) % mod;
        }
    }
    std::cout << f[x] << '\n';
    std::cout << 1ll * g[x] * fac[n] % mod * inv[c[x]] % mod << '\n';
    return 0;
}