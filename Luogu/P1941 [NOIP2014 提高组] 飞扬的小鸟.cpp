#include <iostream>
#include <algorithm>
#include <cstring>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 10000;
const int maxM = 2000;
const int inf = 1e9 + 10;

int n, m, k;
int x[maxN + 10], y[maxN + 10];
int p[maxN + 10], l[maxN + 10], h[maxN + 10];
int v[maxN + 10], u[maxN + 10], d[maxN + 10];
int f[maxN + 10][maxM + 10];
int ans;

int main() {
    promote();
    std::cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) d[i] = 1, u[i] = m;
    for (int i = 1; i <= n; i++) std::cin >> x[i] >> y[i];
    for (int i = 1; i <= k; i++) std::cin >> p[i] >> l[i] >> h[i], v[p[i]] = true, d[p[i]] = l[i] + 1, u[p[i]] = h[i] - 1;
    for (int i = 1; i <= n; i++) for (int j = 0; j <= m; j++) f[i][j] = inf;
    for (int j = 1; j <= m; j++) f[0][j] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = x[i] + 1; j <= m + x[i]; j++) f[i][j] = std::min(f[i - 1][j - x[i]] + 1, f[i][j - x[i]] + 1);
        for (int j = m + 1; j <= m + x[i]; j++) f[i][m] = std::min(f[i][m], f[i][j]);
        for (int j = 1; j <= m - y[i]; j++) f[i][j] = std::min(f[i][j], f[i - 1][j + y[i]]);
        for (int j = 1; j < d[i]; j++) f[i][j] = inf;
        for (int j = m; j > u[i]; j--) f[i][j] = inf;
    }
    ans = inf;
    for (int j = 1; j <= m; j++) ans = std::min(ans, f[n][j]);
    if (ans < inf) {
        std::cout << 1 << '\n';
        std::cout << ans << '\n';
    } else {
        ans = 0;
        int r = 0;
        for (int i = n; i >= 1; i--) {
            for (int j = 1; j <= m; j++) {
                if (f[i][j] < inf) {
                    r = i;
                    break;
                }
            }
            if (r) {
                break;
            }
        }
        for (int i = 1; i <= r; i++) if (v[i]) ans++;
        std::cout << 0 << '\n';
        std::cout << ans << '\n';
    }
    return 0;
}