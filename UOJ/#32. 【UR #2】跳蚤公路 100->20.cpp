#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cstring>

#define int long long

typedef long long lxl;
typedef std::pait<lxl, lxl> pll;

const int maxN = 100;
const int maxM = 10000;
const lxl inf = 1e18;

int n, m;
int u, v, w, s;
lxl f[maxN + 10][maxN + 10][2 * maxN + 10];
int g[maxN + 10][maxN + 10];
std::vector<pll> lim[maxN + 10];

namespace graph {
    struct Vertex {
        int head;
        lxl u;
        lxl d;

        Vertex() {
            u = inf;
            d = - inf;
            return;
        }
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
        int w;
        int s;
    } edge[maxM + 10];

    int ecnt;

    void addEdge(int tail, int head, int w, int s) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        edge[ecnt].w = w;
        edge[ecnt].s = s;
        vertex[tail].head = ecnt;
        return;
    }

    void BellmanFord() {
        f[0][1][0 + n] = 0;
        for (int t = 0; t <= n - 1; t++) {
            memcpy(f[t + 1], f[t], sizeof(f[t]));
            for (int u = 1; u <= n; u++) {
                for (int k = - n; k <= n; k++) {
                    if (f[t][u][k + n] == inf) continue;
                    for (int e = vertex[u].head; e; e = edge[e].next) {
                        int v = edge[e].head;
                        int w = edge[e].w;
                        int s = edge[e].s;
                        if (f[t + 1][v][k + s + n] > f[t][u][k + n] + w) {
                            f[t + 1][v][k + s + n] = f[t][u][k + n] + w;
                        }
                    }
                }
            }
        }
        return;
    }
}

signed main() {
    std::fill(f[0][0], f[0][0] + sizeof(f) / 8, inf);
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) std::cin >> u >> v >> w >> s, graph::addEdge(u, v, w, s), g[u][v] = true;
    for (int k = 1; k <= n; k++) for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) g[i][j] |= g[i][k] && g[k][j];
    graph::BellmanFord();
    for (int i = 1; i <= n; i++) {
        for (int j1 = - n; j1 <= n; j1++) {
            if (f[n][i][j1 + n] == inf) continue;
            lxl d = inf;
            lxl u = - inf;
            lxl di = inf;
            lxl ui = - inf;
            for (int j2 = - n; j2 <= n; j2++) {
                if (f[n - 1][i][j2 + n] == inf) continue;
                lxl k = j1 - j2;
                lxl b = f[n][i][j1 + n] - f[n - 1][i][j2 + n];
                if (b >= inf) continue;
                if (k > 0) d = std::min(d, (lxl) std::ceil(- 1.0 * b / k)), ui = inf;
                if (k < 0) u = std::max(u, (lxl) std::floor(- 1.0 * b / k)), di = - inf;
                if (k == 0) if (b >= 0) di = - inf, ui = inf;
            }
            if (d == inf) d = - inf;
            if (u == - inf) u = inf;
            graph::vertex[i].d = std::max(graph::vertex[i].d, std::min(d, di));
            graph::vertex[i].u = std::min(graph::vertex[i].u, std::max(u, ui));
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (!g[1][j]) continue;
            if (!g[j][i]) continue;
            graph::vertex[i].d = std::max(graph::vertex[i].d, graph::vertex[j].d);
            graph::vertex[i].u = std::min(graph::vertex[i].u, graph::vertex[j].u);
        }
    }
    for (int i = 1; i <= n; i++) {
        if (graph::vertex[i].d == - inf || graph::vertex[i].u == inf) std::cout << -1 << '\n';
        else std::cout << std::max(0ll, graph::vertex[i].u - graph::vertex[i].d + 1) << '\n';
    }
    return 0;
}