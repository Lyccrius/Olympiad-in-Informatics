#include <iostream>

typedef long long lxl;

lxl N, X;

lxl gcd(lxl a, lxl b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main() {
    std::cin >> N >> X;
    std::cout << 3ll * (N - gcd(N, X));
    return 0;
}