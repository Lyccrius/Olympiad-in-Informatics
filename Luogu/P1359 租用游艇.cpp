#include <iostream>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 200;
const int inf = 1e9 + 10;

int n;
int r[maxN + 10][maxN + 10];
int f[maxN + 10][maxN + 10];

int main() {
    promote();
    std::cin >> n;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) f[i][j] = inf;
    for (int i = 1; i <= n; i++) f[i][i] = 0;
    for (int i = 1; i <= n; i++) for (int j = i + 1; j <= n; j++) std::cin >> r[i][j], f[i][j] = r[i][j];
    for (int k = 1; k <= n; k++) for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) f[i][j] = std::min(f[i][j], f[i][k] + f[k][j]);
    std::cout << f[1][n];
    return 0;
}