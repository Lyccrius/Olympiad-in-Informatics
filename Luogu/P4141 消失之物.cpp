#include <iostream>

const int maxN = 2000;
const int maxM = 2000;
const int mod = 10;

int n, m;
int w[maxN + 10];
int f[maxM + 10];
int cnt[maxN + 10][maxM + 10];

int main() {
    f[0] = 1;
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) std::cin >> w[i];
    for (int i = 1; i <= n; i++) {
        for (int j = m; j >= w[i]; j--) {
            f[j] = (f[j] + f[j - w[i]]) % mod;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            cnt[i][j] = f[j];
        }
        for (int j = w[i]; j <= m; j++) {
            cnt[i][j] = (cnt[i][j] - cnt[i][j - w[i]] + mod) % mod;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) std::cout << cnt[i][j];
        std::cout << '\n';
    }
    return 0;
}