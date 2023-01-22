#include <iostream>

const int maxN = 2000;
const int maxM = 2000;
const int mod = 10;

int n, m;
int w[maxN + 10];
int cnt[maxN + 10][maxM + 10];

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) std::cin >> w[i];
    for (int i = 1; i <= n; i++) {
        cnt[i][0] = 1;
        for (int j = 1; j <= n; j++) {
            if (j == i) continue;
            for (int k = m; k >= w[j]; k--) cnt[i][k] = (cnt[i][k] + cnt[i][k - w[j]]) % mod;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) std::cout << cnt[i][j];
        std::cout << '\n';
    }
    return 0;
}