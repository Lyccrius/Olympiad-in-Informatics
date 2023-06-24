#include <iostream>
#include <algorithm>
#include <cmath>

typedef long long lxl;

const int maxN = 9;
const int maxM = 20;
const lxl inf = 1e18;

int n, m;
int u, v, w, s;

namespace graph {
    struct Vertex {
        int head;
        int ins;
        lxl b;
        lxl k;
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

    int dfn;

    void DFS0(int u, lxl b, lxl k) {
        if (vertex[u].ins) {
            b -= vertex[u].b;
            k -= vertex[u].k;
            for (int i = 1; i <= n; i++) {
                if (vertex[i].ins < vertex[u].ins) continue;
                if (k > 0) vertex[i].d = std::max(vertex[i].d, (lxl) std::ceil(- 1.0 * b / k));
                if (k < 0) vertex[i].u = std::min(vertex[i].u, (lxl) std::floor(- 1.0 * b / k));
                if (k == 0) if (b < 0) vertex[i].d = inf, vertex[i].u = - inf;
            }
            return;
        }
        dfn++;
        vertex[u].b = b;
        vertex[u].k = k;
        vertex[u].ins = dfn;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            int w = edge[e].w;
            int s = edge[e].s;
            DFS0(v, b + w, k + s);
        }
        vertex[u].ins = 0;
        dfn--;
        return;
    }

    void DFS1(int u) {
        if (vertex[u].ins) return;
        vertex[u].ins = true;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            vertex[v].d = std::max(vertex[v].d, vertex[u].d);
            vertex[v].u = std::min(vertex[v].u, vertex[u].u);
            DFS1(v);
        }
        vertex[u].ins = false;
        return;
    }
}

signed main() {
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) std::cin >> u >> v >> w >> s, graph::addEdge(u, v, w, s);
    graph::DFS0(1, 0, 0);
    graph::DFS1(1);
    for (int i = 1; i <= n; i++) {
        if (graph::vertex[i].d == - inf || graph::vertex[i].u == inf) std::cout << -1 << '\n';
        else std::cout << std::max(0ll, graph::vertex[i].u - graph::vertex[i].d + 1) << '\n';
    }
    return 0;
}