#include <iostream>

typedef long long lxl;

const int maxK = 1e5;
const int maxA = 1e9;

lxl K;
lxl A[maxK + 10];

int main() {
    std::cin >> K;
    for (int i = 1; i <= K; i++) std::cin >> A[i];
    lxl L = 2;
    lxl R = 2;
    for (int i = K; i >= 1; i--) {
        if (L % A[i] != 0) L = L / A[i] * A[i] + A[i];
        if (R % A[i] != 0) R = R / A[i] * A[i]; R += A[i] - 1;
    }
    if (L > R) {
        std::cout << -1 << '\n';
    } else {
        std::cout << L << ' ' << R << '\n';
    }
    return 0;
}