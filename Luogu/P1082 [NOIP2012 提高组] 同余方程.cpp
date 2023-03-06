#include <iostream>

typedef long long lxl;

lxl a, b;

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

lxl inv(lxl a, lxl b) {
    lxl x, y;
    lxl g = exgcd(a, x, b, y);
    a /= g;
    b /= g;
    x = (x + b) % b;
    return x;
}

int main() {
    std::cin >> a >> b;
    std::cout << inv(a, b);
    return 0;
}