#include <iostream>

typedef long long lxl;

const int maxN = 1000;
const int mod = 998244353;

int T;
int n, k;
int fac[maxN + 10];
int inv[maxN + 10];
int pow[maxN + 10];
int g[maxN + 10];

int ksm(int a, int b) {
    int ret = 1;
    while (b) {
        if (b & 1) ret = 1ll * ret * a % mod;
        a = 1ll * a * a % mod;
        b = b / 2;
    }
    return ret;
}

void init() {
    fac[0] = 1;
    for (int i = 1; i <= maxN; i++) fac[i] = 1ll * fac[i - 1] * i % mod;
    inv[maxN] = ksm(fac[maxN], mod - 2);
    for (int i = maxN; i >= 1; i--) inv[i - 1] = 1ll * inv[i] * i % mod;
    pow[0] = 1;
    for (int i = 1; i <= maxN; i++) pow[i] = 1ll * pow[i - 1] * 2 % mod;
    g[0] = 1;
    for (int i = 2; i <= maxN; i++) g[i] = (1ll * g[i - 1] + 1ll * g[i - 2] * 2 % mod * (i - 1) % mod) % mod * 4 % mod * i % mod * (i - 1) % mod;
    return;
}

int A(int n, int m) {
    return 1ll * fac[n] * inv[n - m] % mod;
}

int C(int n, int m) {
    return 1ll * fac[n] * inv[n - m] % mod * inv[m] % mod;
}

int f(int n, int k) {
    return 1ll * C(n, k) % mod * A(n, k) % mod * pow[k] % mod * g[n - k] % mod;
}

void mian() {
    std::cin >> n;
    for (int k = 0; k <= n; k++) std::cout << f(n, k) << '\n';
    return;
}

int main() {
    init();
    std::cin >> T;
    while (T--) mian();
    return 0;
}