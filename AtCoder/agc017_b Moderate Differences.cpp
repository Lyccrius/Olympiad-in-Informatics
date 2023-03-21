#include <iostream>

typedef long long lxl;

const int maxN = 1e5;

lxl N, A, B, C, D;

int main() {
    std::cin >> N >> A >> B >> C >> D;
    for (int i = 0; i < N; i++) {
        lxl a = i;
        lxl s = N - 1 - i;
        lxl L = A + a * C - s * D;
        lxl R = A + a * D - s * C;
        if (L <= B && B <= R) {
            std::cout << "YES" << '\n';
            return 0;
        }
    }
    std::cout << "NO" << '\n';
    return 0;
}