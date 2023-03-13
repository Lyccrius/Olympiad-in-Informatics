#include <iostream>

const int mod = 1e9 + 7;

const int maxN = 1000;
const int maxM = 1000;
const int maxK = 1000;

int n, m, k;
int c[maxN + 10][maxK * 2 + 10];

int main() {
    std::cin >> n >> m >> k;
    c[0][0] = 1;
    for (int i = 1; i <= maxN; i++) {
        c[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
        }
    }
    std::cout << 1ll * c[n - 1][2 * k] * c[m - 1][2 * k] % mod;
    return 0;
}