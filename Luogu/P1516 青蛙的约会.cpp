#include <iostream>

typedef long long lxl;

lxl x, y, m, n, l;

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

int main() {
    std::cin >> x >> y >> m >> n >> l;
    lxl a = x - y;
    lxl b = n - m;
    if (b < 0) {
        b = - b;
        a = - a;
    }
    lxl g = exgcd(b, x, l, y);
    if (a % g) {
        std::cout << "Impossible";
    } else {
        a /= g;
        l /= g;
        std::cout << ((x * a) % l + l) % l;
    }
    return 0;
}