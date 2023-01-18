#include <iostream>
#include <algorithm>

const int mod = 1e9 + 7;
const int maxN = 100;
const int maxK = 100;

int n, k, d;
long long f[maxN + 10][2];

int main() {
    std::cin >> n >> k >> d;
    f[0][0] = 1;
    f[0][1] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= std::min(i, d - 1); j++) f[i][0] = (f[i][0] + f[i - j][0]) % mod;
        for (int j = 1; j <= std::min(i, k); j++) f[i][1] = (f[i][1] + f[i - j][1]) % mod;
        for (int j = d; j <= std::min(i, k); j++) f[i][1] = (f[i][1] + f[i - j][0]) % mod;
    }
    std::cout << f[n][1];
    return 0;
}