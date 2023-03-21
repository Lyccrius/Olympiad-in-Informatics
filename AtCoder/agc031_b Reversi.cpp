#include <iostream>
#include <algorithm>

const int maxN = 2e5;
const int maxC = 2e5;

const int mod = 1e9 + 7;

int N;
int C[maxN + 10];
int F[maxN + 10];
int L[maxC + 10];

int main() {
    std::cin >> N;
    for (int i = 1; i <= N; i++) std::cin >> C[i];
    N = std::unique(C + 1, C + N + 1) - C - 1;
    F[0] = 1;
    for (int i = 1; i <= N; i++) {
        F[i] = F[i - 1];
        if (L[C[i]]) F[i] = (1ll * F[i] + F[L[C[i]]]) % mod;
        L[C[i]] = i;
    }
    std::cout << F[N] << '\n';
    return 0;
}