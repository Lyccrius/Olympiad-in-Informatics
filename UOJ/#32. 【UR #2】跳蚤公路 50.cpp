#include <iostream>
#include <algorithm>
#include <cmath>

typedef long long lxl;

const int maxN = 40;
const int maxM = 1500;
const lxl inf = 1e18;

int n, m;
int u, v, w, s;
lxl f[maxN + 10][maxN + 10][4 * maxN + 10];
int g[maxN + 10][maxN + 10];

namespace graph {
    struct Vertex {
        lxl u;
        lxl d;

        Vertex() {
            u = inf;
            d = - inf;
            return;
        }
    } vertex[maxN + 10];
}

int main() {
    std::fill(f[0][0], f[0][0] + sizeof(f) / 8, inf);
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) std::cin >> u >> v >> w >> s, f[u][v][s + n] = std::min(f[u][v][s + n], (lxl) w);
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int k1 = - n; k1 <= n; k1++) {
                for (int j = 1; j <= n; j++) {
                    if (f[i][k][k1 + n] == inf) continue;
                    for (int k2 = - n; k2 <= n; k2++) {
                        if (f[k][j][k2 + n] == inf) continue;
                        f[i][j][k1 + k2 + n] = std::min(f[i][j][k1 + k2 + n], f[i][k][k1 + n] + f[k][j][k2 + n]);
                    }
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = - n; k <= n; k++) {
                g[i][j] |= (f[i][j][k + n] != inf);
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (!g[1][j]) continue;
            if (!g[j][j]) continue;
            if (!g[j][i]) continue;
            for (int k = - n; k <= n; k++) {
                if (f[j][j][k + n] == inf) continue;
                lxl b = f[j][j][k + n];
                if (k > 0) graph::vertex[i].d = std::max(graph::vertex[i].d, (lxl) std::ceil(- 1.0 * b / k));
                if (k < 0) graph::vertex[i].u = std::min(graph::vertex[i].u, (lxl) std::floor(- 1.0 * b / k));
                if (k == 0) if (b < 0) graph::vertex[i].d = inf, graph::vertex[i].u = - inf;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (graph::vertex[i].d == - inf || graph::vertex[i].u == inf || graph::vertex[i].u - graph::vertex[i].d + 1 > inf) std::cout << -1 << '\n';
        else std::cout << std::max(0ll, graph::vertex[i].u - graph::vertex[i].d + 1) << '\n';
    }
    return 0;
}