#include <iostream>
#include <algorithm>

typedef long long lxl;

const int maxN = 1e5;

lxl N, K;
lxl A[maxN + 10];
lxl D;
lxl M;

lxl gcd(lxl a, lxl b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main() {
    std::cin >> N >> K;
    for (int i = 1; i <= N; i++) std::cin >> A[i], D = A[i];
    for (int i = 1; i <= N; i++) M = std::max(M, A[i]);
    for (int i = 1; i < N; i++) D = gcd(D, A[i]);
    if (K % D == 0 && K <= M) std::cout << "POSSIBLE";
    else std::cout << "IMPOSSIBLE";
    return 0;
}