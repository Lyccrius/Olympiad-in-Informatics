#include <iostream>

typedef long long lxl;

const lxl mod = 1e9 + 7;
const lxl maxN = 1e5;

int t;
lxl n;

lxl jc[maxN + 10];

void mian() {
    std::cin >> n;
    lxl ans = 0;
    ans = (ans + jc[n]) % mod;
    ans = (ans * n) % mod;
    ans = (ans * (n - 1)) % mod;
    //ans = (ans / 2) % mod;
    //ans = (ans + (n - 1) % mod * n % mod) % mod;
    std::cout << ans << '\n';
    return;
}

void init() {
    jc[1] = 1;
    for (int j = 2; j <= maxN; j++) jc[j] = (jc[j - 1] * j) % mod;
}

int main() {
    init();
    std::cin >> t;
    while (t--) mian();
    return 0;
}