#include <iostream>

typedef long long lxl;

const int maxH = 30;
const int maxW = 30;
const int maxK = 59;
const int maxA = 1e9;
const lxl inf = 1ll * maxK * maxA + 10;

int h, w, k;
int a[maxH + 10][maxW + 10];
lxl f[maxH + 10][maxW + 10][maxK + 10];
lxl ans = inf;

lxl solve(int x, int y) {
    std::fill(f[0][0], f[0][0] + sizeof(f) / 8, inf);
    f[0][0][0] = 0;
    f[0][1][0] = 0;
    f[1][0][0] = 0;
    for (int l = 0; l <= k; l++) {
        for (int i = 1; i <= h; i++) {
            for (int j = 1; j <= w; j++) {
                if (a[i][j] <= a[x][y]) {
                    f[i][j][l] = std::min(f[i][j][l], f[i - 1][j][l]);
                    f[i][j][l] = std::min(f[i][j][l], f[i][j - 1][l]);
                }
                if (a[i][j] >= a[x][y]) {
                    f[i][j][l] = std::min(f[i][j][l], f[i - 1][j][l - 1] + a[i][j]);
                    f[i][j][l] = std::min(f[i][j][l], f[i][j - 1][l - 1] + a[i][j]);
                }
            }
        }
    }
    return f[h][w][k];
}

int main() {
    std::cin >> h >> w >> k;
    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= w; j++) {
            std::cin >> a[i][j];
        }
    }
    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= w; j++) {
            ans = std::min(ans, solve(i, j));
        }
    }
    std::cout << ans << '\n';
    return 0;
}