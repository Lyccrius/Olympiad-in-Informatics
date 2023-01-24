#include <iostream>
#include <algorithm>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 1e3;
const int maxV = 2e4;
const int mod = 998244353;

int n;
int h[maxN + 10];
int f[maxN + 10][maxV * 2 + 10];
int ans;

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> h[i];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            f[i][h[i] - h[j] + maxV] = (f[i][h[i] - h[j] + maxV] + f[j][h[i] - h[j] + maxV] + 1) % mod;
            ans = (ans + f[j][h[i] - h[j] + maxV] + 1) % mod;
        }
    }
    std::cout << (ans + n) % mod;
    return 0;
}