#include <iostream>
#include <cstring>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 1000;
const int maxM = 1000;
const int maxP = 1000;

int n, m, p;
int w[maxN + 10][maxM + 10];
int v[maxN + 10];
int f[maxM + 10];

int main() {
    std::memset(f, 0xcf, sizeof(f));
    f[0] = 0;
    std::cin >> n >> m >> p;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            std::cin >> w[i][j];
        }
    }
    for (int i = 1; i <= n; i++) std::cin >> v[i];
    for (int t = 1; t <= m; t++) {
        for (int i = 1; i <= n; i++) {
            int now = f[t - 1] - v[i];
            for (int k = 0; (t + k) <= m && k < p; k++) {
                int j = i + k;
                if (j > n) j %= n;
                now += w[j][t + k];
                f[t + k] = std::max(f[t + k], now);
            }
        }
    }
    std::cout << f[m];
    return 0;
}