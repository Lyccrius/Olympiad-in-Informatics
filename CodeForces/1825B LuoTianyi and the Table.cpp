#include <iostream>
#include <algorithm>

const int maxN = 100;
const int maxM = 100;
const int maxB = 1e5 + 10;

int t;
int n, m;
int b[maxN + 10][maxM + 10];

void mian() {
    int mn = maxB;
    int mx = - maxB;
    int cn = 0;
    int cx = 0;
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            std::cin >> b[i][j];
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (mn > b[i][j]) {
                mn = b[i][j];
                cn = 0;
            }
            if (mn == b[i][j]) {
                cn++;
            }
            if (mx < b[i][j]) {
                mx = b[i][j];
                cx = 0;
            }
            if (mx == b[i][j]) {
                cx++;
            }
        }
    }
    //printf("mx = %d, mn = %d\n", mx, mn);
    if ((cx >= 2) || (cn >= 2)) {
        std::cout << (mx - mn) * (n * m - 1) << '\n';
        return;
    }
    int sn = maxB;
    int sx = - maxB;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (b[i][j] != mn) {
                sn = std::min(sn, b[i][j]);
            }
            if (b[i][j] != mx) {
                sx = std::max(sx, b[i][j]);
            }
        }
    }
    //printf("sx = %d, sn = %d\n", sx, sn);
    if (n > m) std::swap(n, m);
    //printf("%d * %d + %d * %d * %d = ", (n - 1), std::max(mx - sn, sx - mn), n, (m - 1), (mx - mn));
    std::cout << (n - 1) * std::max(mx - sn, sx - mn) + n * (m - 1) * (mx - mn) << '\n';
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}