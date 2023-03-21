#include <iostream>

typedef long long lxl;

lxl A0, B0, C0, K;

int main() {
    std::cin >> A0 >> B0 >> C0 >> K;
    if (K & 1) std::cout << B0 - A0;
    else std::cout << A0 - B0;
    return 0;
}