#include <iostream>

typedef long long lxl;

const int maxN = 500;
const int maxM = 5000;
const lxl inf = 1e10;

int n, m;
int a[maxN + 10];
int u[maxM + 10], v[maxM + 10], w[maxM + 10];
lxl f[maxN + 10][maxN + 10];

namespace graph {
    struct Vertex {
        int vis;
        int head;
        int match;
        lxl expect;
        lxl weight;
        lxl slack;
    } vertex[2 * maxN + 10];
    
    struct Edge {
        int head;
        int next;
        lxl weight;
    } edge[maxN * maxN + 10];

    int ecnt;
    lxl time;

    void addEdge(int tail, int head, lxl weight) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        edge[ecnt].weight = weight;
        vertex[tail].head = ecnt;
        return;
    }

    lxl f[maxN + 10][maxN + 10];

    void Floyd() {
        for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) f[i][j] = inf;
        for (int i = 1; i <= m; i++) f[u[i]][v[i]] = w[i];
        for (int k = 1; k <= n; k++) {
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    if (f[i][k] == inf) continue;
                    if (f[k][j] == inf) continue;
                    if (f[i][j] > f[i][k] + f[k][j]) {
                        f[i][j] = f[i][k] + f[k][j];
                    }
                }
            }
        }
        for (int i = 1; i <= n; i++) graph::f[i][i] = a[i];
        for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++)  graph::addEdge(i, j + n, - graph::f[i][j]);
        return;
    }

    bool DFS(int u) {
        vertex[u].vis = true;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            lxl w = edge[e].weight;
            lxl gap = vertex[u].expect + vertex[v].expect - w;
            if (vertex[v].vis) continue;
            if (gap == 0) {
                vertex[v].vis = true;
                if (vertex[v].match == 0 || DFS(vertex[v].match)) {
                    vertex[v].match = u;
                    vertex[v].weight = w;
                    return true;
                }
            } else vertex[v].slack = std::min(vertex[v].slack, gap);
        }
        return false;
    }

    lxl KM() {
        lxl ret = 0;
        for (int u = 1; u <= n; u++) vertex[u].expect = - inf;
        for (int u = 1; u <= n; u++) for (int e = vertex[u].head; e; e = edge[e].next) vertex[u].expect = std::max(vertex[u].expect, edge[e].weight);
        for (int u = 1; u <= n; u++) {
            for (int v = 1; v <= n; v++) vertex[v + n].slack = inf;
            for (int v = 1; v <= n; v++) vertex[v + n].vis = false;
            for (int v = 1; v <= n; v++) vertex[v].vis = false;
            while (!DFS(u)) {
                lxl delta = inf;
                for (int v = 1; v <= n; v++) if (vertex[v + n].vis == false) delta = std::min(delta, vertex[v + n].slack);
                for (int v = 1; v <= n; v++) if (vertex[v + n].vis) vertex[v + n].expect += delta;
                for (int v = 1; v <= n; v++) if (vertex[v].vis) vertex[v].expect -= delta;
                for (int v = 1; v <= n; v++) vertex[v + n].vis = false;
                for (int v = 1; v <= n; v++) vertex[v].vis = false;
            }
        }
        for (int u = 1; u <= n; u++) ret += vertex[u + n].weight;
        return ret;
    }
}

signed main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= m; i++) std::cin >> u[i] >> v[i] >> w[i];
    graph::Floyd();
    std::cout << - graph::KM() << '\n';
    return 0;
}