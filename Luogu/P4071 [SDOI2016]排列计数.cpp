#include <iostream>

const int maxT = 5e5;
const int maxN = 1e6;
const int maxM = 1e6;
const int mod = 1e9 + 7;

int t;
int n, m;
int fac[maxN + 10];
int inv[maxN + 10];
int res[maxN + 10];

int pow(int a, int b) {
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
    inv[maxN] = pow(fac[maxN], mod - 2);
    for (int i = maxN - 1; i >= 1; i--) inv[i] = 1ll * inv[i + 1] * (i + 1) % mod;
    res[2] = 1;
    for (int i = 3; i <= maxN; i++) res[i] = 1ll * (i - 1) * (res[i - 2] + res[i - 1]) % mod;
    return;
}

int C(int n, int k) {
    return 1ll * fac[n] * inv[k] % mod * inv[n - k] % mod;
}

int calc(int n, int m) {
    if (m == n - 1) return 0;
    if (m == n) return 1;
    if (m == 0) return res[n];
    return 1ll * C(n, m) * res[n - m] % mod;
}

void mian() {
    std::cin >> n >> m;
    std::cout << calc(n, m) << '\n';
    return;
}

int main() {
    init();
    std::cin >> t;
    while (t--) mian();
    return 0;
}