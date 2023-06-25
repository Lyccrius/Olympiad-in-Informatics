#include <iostream>

typedef char chr;

const int maxN = 200;
const int mod = 998244353;

int n;
chr a[maxN + 10];
int f[maxN + 10];
int fac[maxN + 10];
int inv[maxN + 10];

int main() {
    std::cin >> n;
    for (int i = 0; i < n; i++) std::cin >> a[i];
    f[1] = 1;
    fac[0] = 1;
    fac[1] = 1;
    inv[0] = 1;
    inv[1] = 1;
    for (int i = 2; i <= n; i++) fac[i] = 1ll * fac[i - 1] * i % mod;
    for (int i = 2; i <= n; i++) inv[i] = 1ll * inv[mod % i] * (mod - mod / i) % mod;
    for (int i = 2; i <= n; i++) inv[i] = 1ll * inv[i - 1] * inv[i] % mod;
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            for (int k = 1; j + k < i; k++) {
                if (a[i - 1 - j - k] == '1') {
                    f[i] = (f[i] + 1ll * f[j] * f[k] % mod * fac[i - 1] % mod * inv[j] % mod * inv[k] % mod * inv[i - 1 - j - k] % mod) % mod;
                }
            }
        }
        f[i] = (1ll * f[i] * inv[2]) % mod;
    }
    for (int i = 1; i <= n; i++) std::cout << f[i] << '\n';
    return 0;
}