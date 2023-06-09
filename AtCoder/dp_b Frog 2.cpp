#include <iostream>

const int maxN = 1e5;
const int maxH = 1e4;
const int inf = 1e9;

int n, K;
int h[maxN + 10];
int f[maxN + 10];

int main() {
    std::cin >> n >> K;
    for (int i = 1; i <= n; i++) std::cin >> h[i];
    std::fill(f, f + sizeof(f) / 4, inf);
    f[1] = 0;
    for (int i = 2; i <= n; i++) {
        for (int k = 1; k <= K; k++) {
            int j = i - k;
            if (j < 1) break;
            f[i] = std::min(f[i], f[j] + std::abs(h[i] - h[j]));
        }
    }
    std::cout << f[n] << '\n';
    return 0;
}