#include <iostream>
#include <cmath>

typedef long long lxl;

lxl T;
lxl a, b, c;

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

void mian() {
    std::cin >> a >> b >> c;
    lxl x0;
    lxl y0;
    lxl g = exgcd(a, x0, b, y0);
    if (c % g) {
        std::cout << - 1 << '\n';
        return;
    }
    lxl x1 = x0 * c / g;
    lxl y1 = y0 * c / g;
    lxl dx = b / g;
    lxl dy = a / g;
    lxl xz = x1 + dx * std::ceil((long double) (1 - x1) / dx);
    lxl yz = y1 - dy * std::ceil((long double) (1 - x1) / dx);
    if (yz <= 0) {
        yz = yz + dy * std::ceil(1.0 * (1 - yz) / dy);
        std::cout << xz << ' ';
        std::cout << yz << '\n';
    } else {
        lxl cn = (yz - 1) / dy + 1;
        lxl xn = xz;
        lxl yn = (yz - 1) % dy + 1;
        lxl xx = xz + (yz - 1) / dy * dx;
        lxl yx = yz;
        std::cout << cn << ' ';
        std::cout << xn << ' ';
        std::cout << yn << ' ';
        std::cout << xx << ' ';
        std::cout << yx << '\n';
    }
    return;
}

int main() {
    std::cin >> T;
    while (T--) mian();
    return 0;
}