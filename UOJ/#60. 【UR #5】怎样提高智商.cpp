#include <iostream>

const int mod = 998244353;

int n;

int pow(int a, int b) {
    int ret = 1;
    while (b) {
        if (b & 1) ret = 1ll * ret * a % mod;
        a = 1ll * a * a % mod;
        b = b / 2;
    }
    return ret;
}

int main() {
    std::cin >> n;
    std::cout << 4ll * pow(3, n - 1) % mod << '\n';
    for (int i = 1; i <= n; i++) std::cout << "A 0 0 0 0" << '\n';
    return 0;
}