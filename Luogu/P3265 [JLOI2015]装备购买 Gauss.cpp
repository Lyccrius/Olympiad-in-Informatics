#include <iostream>
#include <algorithm>

typedef double dbl;

const int maxN = 500;
const int maxM = 500;
const int maxA = 1000;
const dbl eps = 1e-5;

int n, m;
int cnt;
int ans;

struct Equipment {
    int a[maxM + 10];
    int c;

    bool operator<(const Equipment &other) const {
        return c < other.c;
    }
} z[maxN + 10];

struct Matrix {
    int n, m;
    dbl a[maxN + 10][maxM + 10];

    void Show() {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                printf("%lf ", a[i][j]);
            }
            printf("\n");
        }
        return;
    }

    void Gauss() {
        for (int i = 1, j = 1; i <= n && j <= m; i++) {
            if (std::abs(a[i][j]) < eps) continue;
            for (int k = m; k >= j; k--) a[i][k] /= a[i][j];
            for (int l = 1; l <= n; l++) if (l != i) for (int k = m; k >= j; k--) a[l][k] -= a[l][j] * a[i][k];
            j++;
        }
        return;
    }
} A;

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) std::cin >> z[i].a[j];
    for (int i = 1; i <= n; i++) std::cin >> z[i].c;
    std::sort(z + 1, z + n + 1);
    A.n = n;
    A.m = m;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) A.a[i][j] = z[i].a[j];
    A.Gauss();
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (A.a[i][j] >= eps) {
                cnt++;
                ans += z[i].c;
                break;
            }
        }
    }
    std::cout << cnt << ' ' << ans << '\n';
    return 0;
}