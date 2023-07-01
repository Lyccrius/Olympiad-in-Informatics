#include <iostream>

const int maxN = 100;
const int maxM = 100;
const int minA = 1;
const int maxA = 1000000;
const int inf = maxA * maxM;

int n, m;
int a[maxN + 10], b[maxN + 10];
int f[maxM + 10][maxM + 10];
int g[maxM + 10][maxM + 10];

bool check(int t) {
    std::fill(f[0], f[0] + sizeof(f) / 4, 0);
    f[0][0] = true;
    for (int k = 1; k <= n; k++) {
        std::fill(g[0], g[0] + sizeof(g) / 4, - inf);
        for (int i = 0; i <= m; i++) for (int j = 0; j <= m; j++) if (f[i][j]) g[i][j] = a[k] * i + b[k] * j;
        for (int i = 0; i <= m; i++) for (int j = 0; j <= m; j++) g[i][j] = std::max(g[i][j], g[i][j - 1]);
        for (int i = 0; i <= m; i++) for (int j = 0; j <= m; j++) g[i][j] = std::max(g[i][j], g[i - 1][j]);
        for (int i = 0; i <= m; i++) for (int j = 0; j <= m; j++) f[i][j] = (g[i][j] >= a[k] * i + b[k] * j - t);
    }
    return f[m][m];
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) std::cin >> a[i] >> b[i];
    int l = minA;
    int r = maxA * maxM;
    while (l < r) {
        int mid = (l + r) / 2;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }
    std::cout << l << '\n';
    return 0;
}