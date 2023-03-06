#include <iostream>

const int maxN = 3e6;

int n, p;
int fac[maxN + 10];
int inv[maxN + 10];

int pow(int a, int b) {
    int ret = 1;
    while (b) {
        if (b & 1) ret = 1ll * ret * a % p;
        a = 1ll * a * a % p;
        b = b / 2;
    }
    return ret;
}

int main() {
    std::cin >> n >> p;
    fac[0] = 1;
    for (int i = 1; i <= n; i++) fac[i] = 1ll * fac[i - 1] * i % p;
    inv[n] = pow(fac[n], p - 2);
    for (int i = n - 1; i >= 0; i--) inv[i] = 1ll * inv[i + 1] * (i + 1) % p;
    for (int i = 1; i <= n; i++) std::cout << 1ll * fac[i - 1] * inv[i] % p << '\n';
    return 0;
}