#include <iostream>

typedef long long lxl;

const lxl maxN = 50;

lxl N, P;
lxl A[maxN + 10];
lxl even;
lxl odd;

int main() {
    std::cin >> N >> P;
    for (int i = 1; i <= N; i++) std::cin >> A[i];
    for (int i = 1; i <= N; i++) if (A[i] & 1) odd++; else even++;
    if (odd == 0) {
        if (P) std::cout << 0;
        else std::cout << (1ll << N);
    } else std::cout << (1ll << (N - 1));
    return 0;
}