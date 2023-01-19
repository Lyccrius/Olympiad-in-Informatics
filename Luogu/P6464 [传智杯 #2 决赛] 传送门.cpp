#include <iostream>
#include <algorithm>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 100;
const int maxM = 5000;
const int inf = 1e9;

int n, m;
int x, y, w;
int f[maxN + 10][maxN + 10];
int F[maxN + 10][maxN + 10];
int ans = inf;

int main() {
    promote();
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) f[i][j] = inf;
    for (int i = 1; i <= n; i++) f[i][i] = 0;
    for (int i = 1; i <= m; i++) std::cin >> x >> y >> w, f[x][y] = w, f[y][x] = w;
    for (int k = 1; k <= n; k++) for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) f[i][j] = std::min(f[i][j], f[i][k] + f[k][j]);
    for (int k = 1; k <= n; k++) for (int l = k + 1; l <= n; l++) {
        for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) F[i][j] = f[i][j];
        F[k][l] = 0, F[l][k] = 0;
        int sum = 0;
        for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) F[i][j] = std::min(F[i][j], F[i][k] + F[k][j]);
        for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) F[i][j] = std::min(F[i][j], F[i][l] + F[l][j]);
        for (int i = 1; i <= n; i++) for (int j = i + 1; j <= n; j++) sum += F[i][j];
        ans = std::min(ans, sum);
    }
    std::cout << ans << '\n';
    return 0;
}