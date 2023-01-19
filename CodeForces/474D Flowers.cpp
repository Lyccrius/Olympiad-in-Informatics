#include <iostream>

typedef long long lxl;

const int maxN = 1e5;
const int mod = 1e9 + 7;

int t, k;
int a, b;

lxl f[maxN + 10];
lxl p[maxN + 10];

int main() {
    std::cin >> t >> k;
    f[0] = 1;
    for (int i = 1; i <= maxN; i++) {
        if (i >= k) f[i] = (f[i] + f[i - k]) % mod;
        f[i] = (f[i] + f[i - 1]) % mod;
        p[i] = (f[i] + p[i - 1]) % mod;
    }
    for (int i = 1; i <= t; i++) {
        std::cin >> a >> b;
        std::cout << (p[b] - p[a - 1] + mod) % mod << '\n';
    }
    return 0;
}