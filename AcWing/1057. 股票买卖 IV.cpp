#include <iostream>
#include <algorithm>

const int maxN = 1e5;
const int maxK = 100;
const int inf = 1e9 + 10;

int n, k;
int a[maxN + 10];
int f[maxN + 10][maxK + 10][2];
int ans;

int main() {
    std::cin >> n >> k;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 0; i <= n; i++) f[i][0][0] = 0, f[i][0][1] = - inf;
    for (int i = 0; i <= n; i++) for (int j = 1; j <= k; j++) f[i][j][0] = - inf, f[i][j][1] = - inf;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= k; j++) {
        f[i][j][0] = std::max(f[i - 1][j][0], f[i - 1][j][1] + a[i]);
        f[i][j][1] = std::max(f[i - 1][j][1], f[i - 1][j - 1][0] - a[i]);
    }
    for (int j = 0; j <= k; j++) ans = std::max(ans, f[n][j][0]);
    std::cout << ans;
    return 0;
}