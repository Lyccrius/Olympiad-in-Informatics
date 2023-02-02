#include <iostream>
#include <string>

typedef long long lxl;

lxl N, M;
std::string S;
std::string T;

lxl gcd(lxl a, lxl b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main() {
    std::cin >> N >> M;
    std::cin >> S;
    std::cin >> T;
    lxl g = gcd(N, M);
    for (lxl c = 0; c < g; c++) {
        if (S[N / g * c] != T[M / g * c]) {
            std::cout << -1;
            return 0;
        }
    }
    std::cout << N * M / g;
    return 0;
}