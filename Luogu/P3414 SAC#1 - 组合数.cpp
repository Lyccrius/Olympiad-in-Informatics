#include <iostream>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef long long lxl;

const int mod = 6662333;
const lxl maxN = 1e18;

lxl n;

lxl pow(lxl a, lxl b) {
    lxl ans = 1;
    while (b) {
        if (b & 1) ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ans;
}

int main() {
    std::cin >> n;
    std::cout << pow(2, n - 1);
    return 0;
}