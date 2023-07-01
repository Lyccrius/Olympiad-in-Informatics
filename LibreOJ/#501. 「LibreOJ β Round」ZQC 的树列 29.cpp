#include <iostream>
#include <cmath>

typedef long long lxl;

lxl k;

int main() {
    std::cin >> k;
    if (k == pow(2, log2(k))) {
        std::cout << log2(k) + 2 << '\n';
        for (int i = 1; i <= log2(k) + 2; i++) std::cout << i << ' ';
        std::cout << '\n';
    } else {
        std::cout << "qnq" << '\n';
    }
    return 0;
}