#include <iostream>
#include <iomanip>

typedef double dbl;

const int maxN = 10;
const dbl eps = 1e-6;

int n;
dbl a[maxN + 10][maxN + 10];

struct Matrix {
    int n;
    int m;
    dbl a[maxN + 10][maxN + 10];

    void show() {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                std::cout << a[i][j] << ' ';
            }
            std::cout << '\n';
        }
        return;
    }

    bool Gauss() {
        for (int i = 1; i <= n; i++) {
            int i_;
            for (i_ = i; i_ <= n; i_++) if (std::abs(a[i_][i]) >= eps) break;
            if (i_ > n) return false;
            for (int j = 1; j <= m; j++) std::swap(a[i][j], a[i_][j]);
            for (int j = m; j >= i; j--) a[i][j] /= a[i][i];
            for (i_ = 1; i_ <= n; i_++) if (i_ != i) for (int j = m; j >= i; j--) a[i_][j] -= a[i_][i] * a[i][j];
        }
        return true;
    }
} A;

int main() {
    std::cin >> n;
    for (int i = 1; i <= n + 1; i++) {
        for (int j = 1; j <= n; j++ ){
            std::cin >> a[i][j];
        }
    }
    A.n = n;
    A.m = n + 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            A.a[i][j] = 2 * (a[i][j] - a[i + 1][j]);
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            A.a[i][n + 1] += a[i][j] * a[i][j] - a[i + 1][j] * a[i + 1][j];
        }
    }
    //A.show();
    A.Gauss();
    std::cout << std::setiosflags(std::ios::fixed);
    for (int i = 1; i <= n; i++) std::cout << std::setprecision(3) << A.a[i][n + 1] << ' ';
    return 0;
}