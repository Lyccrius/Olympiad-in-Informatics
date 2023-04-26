#include <iostream>
#include <cmath>

typedef long long lxl;

int T;
lxl g, l;

void mian() {
    std::cin >> g >> l;
    std::cout << 2 * (long long) sqrt(l / g) * g << ' ' << l + g << '\n';
    return;
}

int main() {
    std::cin >> T;
    while (T--) mian();
    return 0;
}