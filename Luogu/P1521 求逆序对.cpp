#include <iostream>

const int maxN = 100;
const int maxK = 5000;
const int mod = 10000;

int n, k;
int f[maxN + 10][maxK + 10];

int main() {
    std::cin >> n >> k;
    for (int i = 1; i <= n; i++) f[i][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= std::min(k, i * (i - 1) / 2); j++) {
            for (int l = j - i + 1; l <= j; l++) {
                f[i][j] = (f[i][j] + f[i - 1][l]) % mod;
            }
        }
    }
    std::cout << f[n][k];
    return 0;
}