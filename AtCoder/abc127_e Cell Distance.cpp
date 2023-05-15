#include <iostream>

const int mod = 1e9 + 7;

int n, m, k;
int ans = 0;

int pow(int a, int b) {
    int ret = 1;
    while (b) {
        if (b & 1) ret = 1ll * ret * a % mod;
        a = 1ll * a * a % mod;
        b = b / 2;
    }
    return ret;
}

int inv(int x) {
    return pow(x, mod - 2);
}

int C(int n, int m) {
    int p = 1;
    int q = 1;
    for (int i = 1; i <= m; i++) {
        p = 1ll * p * (n - m + i) % mod;
        q = 1ll * q * i % mod;
    }
    return 1ll * p * inv(q) % mod;
}

int main() {
    std::cin >> n >> m >> k;
    for (int i = 1; i < n; i++) ans = (ans + 1ll * (n - i) * i % mod * m % mod * m % mod) % mod;
    for (int i = 1; i < m; i++) ans = (ans + 1ll * (m - i) * i % mod * n % mod * n % mod) % mod;
    ans = 1ll * ans * C(n * m - 2, k - 2) % mod;
    std::cout << ans << '\n';
    return 0;
}