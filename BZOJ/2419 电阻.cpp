#include <iostream>
#include <iomanip>

typedef double dbl;

const int maxN = 500;
const dbl eps = 1e-6;

int n, m;
int x, y, r;

struct Matrix {
    int n, m;
    dbl a[maxN + 10][maxN + 10];

    void clear() {
        std::fill(a[0], a[0] + sizeof(a) / 8, 0);
        return;
    }

    void Gauss() {
        for (int i = 1; i <= n; i++) {
            for (int j = i; j <= n; j++) {
                if (std::abs(a[j][i]) >= eps) {
                    for (int k = i; k <= m; k++) std::swap(a[i][k], a[j][k]);
                }
            }
            if (std::abs(a[i][i]) < eps) return;
            for (int j = m; j >= i; j--) a[i][j] /= a[i][i];
            for (int k = 1; k <= n; k++) if (k != i) for (int j = m; j >= i; j--) a[k][j] -= a[k][i] * a[i][j];
        }
        return;
    }
} A, R;

void mian() {
    A.clear();
    R.clear();
    A.n = n;
    A.m = n + 1;
    A.a[1][n + 1] = 1;
    A.a[n][n] = 1;
    A.a[n][n + 1] = 0;
    for (int i = 1; i <= m; i++) {
        std::cin >> x >> y >> r;
        if (x == y) continue;
        R.a[x][y] += 1.0 / r;
        R.a[y][x] += 1.0 / r;
    }
    for (int i = 1; i <= n - 1; i++) {
        for (int j = 1; j <= n; j++) {
            A.a[i][i] += R.a[i][j];
            A.a[i][j] -= R.a[i][j];
        }
    }
    A.Gauss();
    std::cout << std::setiosflags(std::ios::fixed);
    std::cout << std::setprecision(2) << A.a[1][n + 1] << '\n';
    return;
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) mian();
    return 0;
}