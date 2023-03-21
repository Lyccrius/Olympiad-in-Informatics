#include <iostream>

typedef long long lxl;

int T;
lxl A, B, C, D;

lxl gcd(lxl a, lxl b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

void mian() {
    std::cin >> A >> B >> C >> D;
    if (A < B) {
        std::cout << "No" << '\n';
        return;
    }
    if (B > D) {
        std::cout << "No" << '\n';
        return;
    }
    lxl G = gcd(B, D);
    if ((A - C - 1) / G > (A - B) / G) {
        std::cout << "No" << '\n';
    } else {
        std::cout << "Yes" << '\n';
    }
    return;
}

int main() {
    std::cin >> T;
    while (T--) mian();
    return 0;
}