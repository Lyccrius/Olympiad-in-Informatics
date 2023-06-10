#include <iostream>
#include <iomanip>
#include <algorithm>

typedef long long lxl;

const int maxN = 100;
const int maxW = 100;
const lxl inf = 1e10 + 10;

int t;
int n, w;
lxl u[maxN + 10];
lxl f[maxN + 10][maxW + 10];

void mian() {
    std::cin >> n >> w;
    for (int i = 1; i <= n; i++) std::cin >> u[i];
    std::sort(u + 1, u + n + 1);
    std::reverse(u + 1, u + n + 1);
    for (int i = 1; i <= n; i++) u[i] += u[i - 1];
    std::fill(f[0], f[0] + sizeof(f) / 8, inf);
    f[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            for (int k = 1; k <= w; k++) {
                f[i][k] = std::min(f[i][k], f[j][k - 1] + 1ll * i * (u[i] - u[j]));
            }
        }
    }
    std::cout << std::setiosflags(std::ios::fixed);
    std::cout << std::setprecision(4) << 1.0 * f[n][w] / u[n] << '\n';
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}