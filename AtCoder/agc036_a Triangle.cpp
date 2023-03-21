#include <iostream>
#include <cmath>

typedef long long lxl;

lxl S;
lxl X1, Y1, X2, Y2, X3, Y3;

int main() {
    std::cin >> S;
    X1 = 0;
    Y1 = 0;
    X2 = std::ceil(std::sqrt(S));
    Y2 = X2 * X2 - S;
    X3 = 1;
    Y3 = X2;
    std::cout << X1 << ' ' << Y1 << ' ' << X2 << ' ' << Y2 << ' ' << X3 << ' ' << Y3;
    return 0;
}