#include <iostream>
#include <algorithm>

typedef long long lxl;

lxl Q, H, S, D;
lxl N;

int main() {
    std::cin >> Q >> H >> S >> D;
    std::cin >> N;
    Q *= 4;
    H *= 2;
    S = std::min(S, Q);
    S = std::min(S, H);
    if (S * 2 < D) {
        std::cout << N * S;
    } else {
        std::cout << (N / 2) * D + (N % 2) * S;
    }
    return 0;
}