#include <iostream>

typedef long long lxl;

const lxl mod = 9;

lxl Q;
lxl l, r;

lxl exgcd(lxl a, lxl &x, lxl b, lxl &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    lxl g = exgcd(b, y, a % b, x);
    y -= a / b * x;
    return g;
}

lxl inv(lxl a) {
    lxl x, y;
    lxl g = exgcd(a, x, mod, y);
    return x;
}

void mian() {
    std::cin >> l >> r;
    std::cout << ((l + r) % mod * (r - l + 1) % mod * inv(2) % mod + mod) % mod << '\n';
    return;
}

int main() {
    std::cin >> Q;
    while (Q--) mian();
    return 0;
}