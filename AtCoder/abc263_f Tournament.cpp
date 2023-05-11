#include <iostream>

typedef long long lxl;

const int maxN = 16;
const int maxM = 65536;

int n, m;
lxl c[maxM + 10][maxN + 10];
lxl f[maxM + 10][maxN + 10];

lxl solve(int u, int p) {
    if (u >= m) return c[(u ^ m) + 1][p];
    if (~f[u][p]) return f[u][p];
    return f[u][p] = std::max(solve(2 * u, p + 1) + solve(2 * u + 1, 0), solve(2 * u, 0) + solve(2 * u + 1, p + 1));
}

int main() {
    std::fill(f[0], f[0] + sizeof(f) / 8, -1);
    std::cin >> n;
    m = (1 << n);
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            std::cin >> c[i][j];
        }
    }
    std::cout << solve(1, 0) << '\n';
    return 0;
}