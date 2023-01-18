#include <iostream>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 1000;
const int maxM = 1000;

int n, m;
double a[maxN + 10][maxM + 10];
double b[maxN + 10][maxM + 10];
int K;
int x[maxN * maxN + 10];
int y[maxN * maxN + 10];

int main() {
    std::cin >> m >> n;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) std::cin >> a[i][j];
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) std::cin >> b[i][j];
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) a[i][m + 1] += a[i][j];
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) b[i][m + 1] += b[i][j];
    for (int i = 1; i <= n; i++) a[i][m + 1] /= m;
    for (int i = 1; i <= n; i++) b[i][m + 1] /= m;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) a[i][m + 2] += (a[i][j] - a[i][m + 1]) * (a[i][j] - a[i][m + 1]);
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) b[i][m + 2] += (b[i][j] - b[i][m + 1]) * (b[i][j] - b[i][m + 1]);
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (a[i][m + 2] + b[i][m + 2] > a[j][m + 2] + b[j][m + 2]) {
                std::swap(a[i][m + 2], a[j][m + 2]);
                std::swap(b[i][m + 2], b[j][m + 2]);
                K++;
                x[K] = i;
                y[K] = j;
            }
        }
    }
    std::cout << K << '\n';
    for (int i = 1; i <= K; i++) std::cout << x[i] << ' ' << y[i] << '\n';
    return 0;
}