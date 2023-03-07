#include <iostream>

typedef long long lxl;

const int mod = 998244353;

lxl l, r;

int g(lxl n) {
    int ret = 0;
    for (lxl i = 1, j; i <= n; i = j + 1) {
        j = n / (n / i);
        ret = (1ll * ret + 1ll * (j - i + 1) * (n / i)) % mod;
    }
    return ret;
}

int main() {
    std::cin >> l >> r;
    std::cout << (g(r) - g(l - 1) + mod) % mod;
    return 0;
}