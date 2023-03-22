#include <iostream>

typedef double dbl;
typedef long long lxl;

const int maxN = 100;
const int maxM = 4500;
const int maxC = 1000;
const lxl inf = 1e10 + 10;

int n, m;
int a, b, c;
lxl dis[maxN + 10][maxN + 10];
lxl cnt[maxN + 10][maxN + 10];
dbl ans[maxN + 10];

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) dis[i][j] = inf;
    for (int i = 1; i <= n; i++) dis[i][i] = 0;
    for (int i = 1; i <= n; i++) cnt[i][i] = 1;
    for (int i = 1; i <= m; i++) {
        std::cin >> a >> b >> c;
        dis[a][b] = c;
        dis[b][a] = c;
        cnt[a][b] = 1;
        cnt[b][a] = 1;
    }
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (k == i) continue;
                if (k == j) continue;
                if (dis[i][j] > dis[i][k] + dis[k][j]) {
                    dis[i][j] = dis[i][k] + dis[k][j];
                    cnt[i][j] = cnt[i][k] * cnt[k][j];
                    continue;
                }
                if (dis[i][j] == dis[i][k] + dis[k][j]) {
                    cnt[i][j] += cnt[i][k] * cnt[k][j];
                }
            }
        }
    }
    /*
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (k == i) continue;
                if (k == j) continue;
                if (dis[i][j] == dis[i][k] + dis[k][j]) {
                    cnt[i][j] += cnt[i][k] * cnt[k][j];
                }
            }
        }
    }
    */
    for (int v = 1; v <= n; v++) {
        for (int s = 1; s <= n; s++) {
            for (int t = 1; t <= n; t++) {
                if (v == s) continue;
                if (v == t) continue;
                if (dis[s][t] == dis[s][v] + dis[v][t]) {
                    ans[v] += 1.0 * cnt[s][v] * cnt[v][t] / cnt[s][t];
                }
            }
        }
    }
    for (int v = 1; v <= n; v++) {
        printf("%.3lf\n", ans[v]);
    }
    return 0;
}