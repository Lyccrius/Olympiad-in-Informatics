#include <iostream>

const int maxN = 3e6;

int n, p;
int inv[maxN + 10];

int main() {
    std::cin >> n >> p;
    inv[1] = 1;
    for (int i = 2; i <= n; i++) inv[i] = (p - 1ll * inv[p % i] * (p / i) % p);
    for (int i = 1; i <= n; i++) std::cout << inv[i] << '\n';
    return 0;
}