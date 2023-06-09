#include <iostream>

const int maxN = 1e5;
const int maxH = 1e4;
const int inf = 1e9;

int n;
int h[maxN + 10];
int f[maxN + 10];

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> h[i];
    std::fill(f, f + sizeof(f) / 4, inf);
    f[1] = 0;
    for (int i = 2; i <= n; i++) f[i] = std::min(f[i - 1] + std::abs(h[i] - h[i - 1]), f[i - 2] + std::abs(h[i] - h[i - 2]));
    std::cout << f[n] << '\n';
    return 0;
}