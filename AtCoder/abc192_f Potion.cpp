#include <iostream>
#include <algorithm>

typedef long long lxl;

const int maxN = 100;
const lxl inf = 1e18;

int n;
lxl x;
int a[maxN + 10];
int b[maxN + 10];
lxl f[maxN + 10][maxN + 10][maxN + 10];
lxl g[maxN + 10][maxN + 10][maxN + 10];
lxl ans = inf;

lxl calc(int m) {
    for (int i = 1; i <= n; i++) b[i] = a[i] % m;
    //printf("m = %d\n", m);
    //printf("b = ");
    //for (int i = 1; i <= n; i++) printf("%d ", b[i]); printf("\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 0; k < m; k++) {
                f[i][j][k] = 0;
                g[i][j][k] = 0;
            }
        }
    }
    f[0][0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= std::min(i, m); j++) {
            for (int k = 0; k < m; k++) {
                f[i][j][k] = f[i - 1][j][k];
                g[i][j][k] = g[i - 1][j][k];
            }
        }
        for (int j = 1; j <= std::min(i, m); j++) {
            for (int k = 0; k < m; k++) {
                if (f[i - 1][j - 1][(k - b[i] + m) % m]) {
                    f[i][j][k] = true;
                    g[i][j][k] = std::max(g[i][j][k], g[i - 1][j - 1][(k - b[i] + m) % m] + a[i]);
                    //printf("g[%d][%d][%d] = %d\n", i, j, k, g[i][j][k]);
                }
            }
        }
    }
    //printf("g = %d\n", g[n][m][x % m]);
    //printf("ret = %lld\n", (x - g[n][m][x % m]) / m);
    if (f[n][m][x % m]) {
        return (x - g[n][m][x % m]) / m;
    } else {
        return inf;
    }
}

int main() {
    std::cin >> n >> x;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) ans = std::min(ans, calc(i));
    std::cout << ans << '\n';
    return 0;
}