#include <iostream>

typedef long long lxl;

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

int t;
lxl n, a, b;

void mian() {
    std::cin >> n >> a >> b;
    lxl m = n % b;
    if (n == 1) {
        std::cout << "YES" << '\n';
        return;
    }
    if (a == 1) {
        if (m == 1 || b == 1) {
            std::cout << "YES" << '\n';
        } else {
            std::cout << "NO" << '\n';
        }
        return;
    }
    for (lxl i = 1; i <= n; i *= a) {
        if (i % b == m) {
            std::cout << "YES" << '\n';
            return;
        }
        if (i * a == i) break;
    }
    std::cout << "NO" << '\n';
    return;
}

int main() {
    promote();
    std::cin >> t;
    while (t--) mian();
    return 0;
}