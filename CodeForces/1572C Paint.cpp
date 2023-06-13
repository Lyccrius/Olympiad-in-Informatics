#include <iostream>
#include <vector>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef std::vector<int> vic;

const int maxN = 3000;

int t;
int n, m;
int a[maxN + 10];
int b[maxN + 10];
int x[maxN + 10];
int p[maxN + 10];
int f[maxN + 10][maxN + 10];

void mian() {
    std::cin >> n, m = 0;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) if (a[i] != a[i - 1]) b[++m] = a[i];
    for (int i = 1; i <= n; i++) x[i] = 0;
    for (int i = 1; i <= m; i++) p[i] = x[b[i]], x[b[i]] = i;
    for (int i = 1; i <= m; i++) for (int j = 1; j <= m; j++) f[i][j] = maxN;
    for (int i = 1; i <= m; i++) f[i][i] = 0, f[i + 1][i] = 0;
    for (int l = 2; l <= m; l++) {
        for (int i = 1; i + l - 1 <= m; i++) {
            int j = i + l - 1;
            f[i][j] = std::min(f[i + 1][j], f[i][j - 1]) + 1;
            for (int k = p[j]; k >= i; k = p[k]) f[i][j] = std::min(f[i][j], f[i][k] + f[k + 1][j]);
        }
    }
    std::cout << f[1][m] << '\n';
    return;
}

int main() {
    promote();
    std::cin >> t;
    while (t--) mian();
    return 0;
}