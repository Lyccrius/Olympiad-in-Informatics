#include <iostream>
#include <iomanip>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cout << std::setiosflags(std::ios::fixed);
    return;
}

typedef double dbl;

const int maxN = 2000;
const int maxM = 2000;
const int maxV = 300;
const int maxE = 90000;
const int maxW = 100;
const int inf = 1e9;

int n, m, v, e;
int c[maxN + 10];
int d[maxN + 10];
dbl k[maxN + 10];
int a[maxE + 10], b[maxE + 10], w[maxE + 10];

namespace graph {
    int dis[maxN + 10][maxN + 10];

    void Floyd() {
        for (int i = 1; i <= v; i++) for (int j = 1; j <= v; j++) graph::dis[i][j] = inf;
        for (int i = 1; i <= v; i++) graph::dis[i][i] = 0;
        for (int j = 1; j <= e; j++) {
            graph::dis[a[j]][b[j]] = std::min(graph::dis[a[j]][b[j]], w[j]);
            graph::dis[b[j]][a[j]] = std::min(graph::dis[b[j]][a[j]], w[j]);
        }
        for (int k = 1; k <= v; k++) {
            for (int i = 1; i <= v; i++) {
                for (int j = 1; j <= v; j++) {
                    graph::dis[i][j] = std::min(dis[i][j], graph::dis[i][k] + graph::dis[k][j]);
                }
            }
        }
        return;
    }
}

dbl f[maxN + 10][maxM + 10][2];
dbl ans;

int main() {
    promote();
    std::cin >> n >> m >> v >> e;
    for (int i = 1; i <= n; i++) std::cin >> c[i];
    for (int i = 1; i <= n; i++) std::cin >> d[i];
    for (int i = 1; i <= n; i++) std::cin >> k[i];
    for (int j = 1; j <= e; j++) std::cin >> a[j] >> b[j] >> w[j];
    graph::Floyd();
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            f[i][j][0] = inf;
            f[i][j][1] = inf;
        }
    }
    f[1][0][0] = 0;
    f[1][1][1] = 0;
    for (int i = 2; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            f[i][j][0] = std::min(f[i - 1][j][0] + graph::dis[c[i - 1]][c[i]],
                                  f[i - 1][j][1] + k[i - 1] * graph::dis[d[i - 1]][c[i]] + (1 - k[i - 1]) * graph::dis[c[i - 1]][c[i]]);
            if (!j) continue;
            f[i][j][1] = std::min(f[i - 1][j - 1][0] + k[i] * graph::dis[c[i - 1]][d[i]] + (1 - k[i]) * graph::dis[c[i - 1]][c[i]],  
                                  f[i - 1][j - 1][1] + k[i - 1] * k[i] * graph::dis[d[i - 1]][d[i]] + k[i - 1] * (1 - k[i]) * graph::dis[d[i - 1]][c[i]] + (1 - k[i - 1]) * k[i] * graph::dis[c[i - 1]][d[i]] + (1 - k[i - 1]) * (1 - k[i]) * graph::dis[c[i - 1]][c[i]]);
        }
    }
    ans = inf;
    for (int j = 0; j <= m; j++) {
        ans = std::min(ans, f[n][j][0]);
        ans = std::min(ans, f[n][j][1]);
    }
    std::cout << std::setprecision(2) << ans;
    return 0;
}