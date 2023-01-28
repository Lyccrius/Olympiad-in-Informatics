#include <iostream>
#include <algorithm>

const int maxN = 2e5;

int t;
long long x;

void mian() {
    std::cin >> x;
    long long a = x / 2 + x;
    long long b = x / 2;
    bool ok = true;
    if ((a ^ b) != x) ok = false;
    if (a + b != x * 2) ok = false;
    if (ok) std::cout << a << ' ' << b << '\n';
    else std::cout << -1 << '\n';
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}