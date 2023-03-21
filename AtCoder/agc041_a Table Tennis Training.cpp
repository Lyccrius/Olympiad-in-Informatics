#include <iostream>

typedef long long lxl;

lxl N, A, B;

int main() {
    std::cin >> N >> A >> B;
    if ((B - A) % 2) {
        std::cout << (B - A) / 2 + std::min(A - 1, N - B) + 1;
    } else {
        std::cout << (B - A) / 2;
    }
    return 0;
}