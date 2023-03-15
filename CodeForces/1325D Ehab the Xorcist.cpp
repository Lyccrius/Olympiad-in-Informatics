#include <iostream>

typedef long long lxl;

lxl u, v;

int main() {
    std::cin >> u >> v;
    if (u > v) {
        std::cout << -1;
    } else if ((u & 1) != (v & 1)) {
        std::cout << -1;
    } else if (v == 0) {
        std::cout << 0;
    } else if (u == v) {
        std::cout << 1 << '\n';
        std::cout << u;
    } else if ((u & ((v - u) / 2)) == 0) {
        std::cout << 2 << '\n';
        std::cout << (v - u) / 2 << ' ' << (v - u) / 2 + u;
    } else {
        std::cout << 3 << '\n';
        std::cout << (v - u) / 2 << ' ' << (v - u) / 2 << ' ' << u;
    }
    return 0;
}