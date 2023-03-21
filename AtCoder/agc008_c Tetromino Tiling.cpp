#include <iostream>

typedef long long lxl;

lxl I, O, T, J, L, S, Z;
lxl K1, K2;

int main() {
    std::cin >> I >> O >> T >> J >> L >> S >> Z;
    K1 = O + (I / 2 * 2) + (J / 2 * 2) + (L / 2 * 2) + ((I & 1) && (J & 1) && (L & 1)) * 3;
    K2 = O + ((I - 1) / 2 * 2) + ((J - 1) / 2 * 2) + ((L - 1) / 2 * 2) + (I && J && L) * 3;
    std::cout << std::max(K1, K2);
    return 0;
}