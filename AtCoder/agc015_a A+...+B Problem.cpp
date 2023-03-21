#include <iostream>

typedef long long lxl;

lxl N, A, B;

int main() {
    std::cin >> N >> A >> B;
    if (N == 1) {
        if (A == B) std::cout << 1;
        else std::cout << 0;
    } else {
        if (A <= B) std::cout << (N - 2) * (B - A) + 1;
        else std::cout << 0;
    }
    return 0;
}