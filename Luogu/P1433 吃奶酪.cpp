#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>

const int maxN = 15;
const int dx[5] = {0, -1, 0, 1, 0};
const int dy[5] = {0, 0, 1, 0, -1};
const int inf = 1e9;

int n;
double x[maxN + 10];
double y[maxN + 10];

double Dis(int a, int b) {
    double deltaX = x[a] - x[b];
    double deltaY = y[a] - y[b];
    return std::sqrt(deltaX * deltaX + deltaY * deltaY);
}

double dis[maxN + 10][maxN + 10];
double f[(1 << maxN) + 10][maxN + 10];
double ans;

int main() {
    std::fill(f[0], f[0] + ((1 << maxN) + 10) * (maxN + 10), inf);
    std::cin >> n;
    for (int i = 1; i <= n; i++) f[0][i] = 0;
    for (int i = 1; i <= n; i++) std::cin >> x[i] >> y[i];
    for (int i = 1; i <= n; i++) for (int j = 0; j < i; j++) dis[i][j] = dis[j][i] = Dis(i, j);
    //for (int i = 1; i <= n; i++) for (int j = 0; j < i; j++) printf("dis[%d][%d] = %lf\n", i, j, dis[i][j]);
    for (int i = 1; i <= n; i++) f[1 << (i - 1)][i] = dis[0][i];
    for (int s = 1; s <= (1 << n) - 1; s++) {
        for (int i = 1; i <= n; i++) {
            if (s & (1 << (i - 1))) continue;
            for (int j = 1; j <= n; j++) {
                if (s & (1 << (j - 1))) {
                    f[s ^ (1 << (i - 1))][i] = std::min(f[s ^ (1 << (i - 1))][i], f[s][j] + dis[i][j]);
                }
            }
            //printf("f[%d][%d] = %lf\n", s ^ (1 << (i - 1)), i, f[s ^ (1 << (i - 1))][i]);
        }
    }
    ans = inf;
    for (int i = 1; i <= n; i++) ans = std::min(ans, f[(1 << n) - 1][i]);
    printf("%.2lf\n", ans);
    return 0;
}