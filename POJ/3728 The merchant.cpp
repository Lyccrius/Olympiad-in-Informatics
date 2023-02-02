#include <iostream>
#include <algorithm>

const int maxN = 5e4;
const int logN = 16;
const int inf = 1e9;

int N;
int w[maxN + 10];
int u, v;
int Q;

namespace graph {
    struct Vertex {
        int head;
        int dep;
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
    } edge[maxN * 2 + 10];

    int ecnt;

    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    struct SparseTable {
        int fa[maxN + 10][logN + 5];
        int mx[maxN + 10][logN + 5];
        int mn[maxN + 10][logN + 5];
        int up[maxN + 10][logN + 5];
        int dw[maxN + 10][logN + 5];

        int QueryMx(int u, int lca) {
            int ret = 0;
            for (int p = logN; p >= 0; p--) {
                if (vertex[fa[u][p]].dep >= vertex[lca].dep) {
                    ret = std::max(ret, mx[u][p]);
                    u = fa[u][p];
                }
            }
            return ret;
        }

        int QueryMn(int u, int lca) {
            int ret = inf;
            for (int p = logN; p >= 0; p--) {
                if (vertex[fa[u][p]].dep >= vertex[lca].dep) {
                    ret = std::min(ret, mn[u][p]);
                    u = fa[u][p];
                }
            }
            return ret;
        }

        int QueryUp(int u, int lca) {
            int ret = 0;
            int t = inf;
            for (int p = logN; p >= 0; p--) {
                if (vertex[fa[u][p]].dep >= vertex[lca].dep) {
                    ret = std::max(ret, up[u][p]);
                    ret = std::max(ret, mx[u][p] - t);
                    t = std::min(t, mn[u][p]);
                    u = fa[u][p];
                }
            }
            return ret;
        }

        int QueryDw(int u, int lca) {
            int ret = 0;
            int t = 0;
            for (int p = logN; p >= 0; p--) {
                if (vertex[fa[u][p]].dep >= vertex[lca].dep) {
                    ret = std::max(ret, dw[u][p]);
                    ret = std::max(ret, t - mn[u][p]);
                    t = std::max(t, mx[u][p]);
                    u = fa[u][p];
                }
            }
            return ret;
        }
    } ST;

    void DFS(int u, int from) {
        vertex[u].dep = vertex[from].dep + 1;
        ST.fa[u][0] = from;
        for (int p = 1; p <= logN; p++) {
            int t = ST.fa[u][p - 1];
            ST.fa[u][p] = ST.fa[t][p - 1];
            ST.mx[u][p] = std::max(ST.mx[u][p - 1], ST.mx[t][p - 1]);
            ST.mn[u][p] = std::min(ST.mn[u][p - 1], ST.mn[t][p - 1]);
            ST.up[u][p] = std::max(std::max(0, ST.mx[t][p - 1] - ST.mn[u][p - 1]), std::max(ST.up[u][p - 1], ST.up[t][p - 1]));
            ST.dw[u][p] = std::max(std::max(0, ST.mx[u][p - 1] - ST.mn[t][p - 1]), std::max(ST.dw[u][p - 1], ST.dw[t][p - 1]));
        }
        for (int e = vertex[u].head; e; e = edge[e].next ){
            int v = edge[e].head;
            if (v == from) continue;
            ST.mx[v][0] = std::max(w[u], w[v]);
            ST.mn[v][0] = std::min(w[u], w[v]);
            ST.up[v][0] = std::max(0, w[u] - w[v]);
            ST.dw[v][0] = std::max(0, w[v] - w[u]);
            DFS(v, u);
        }
        return;
    }

    int LCA(int u, int v) {
        if (vertex[u].dep < vertex[v].dep) std::swap(u, v);
        for (int p = logN; p >= 0; p--) if (vertex[ST.fa[u][p]].dep >= vertex[v].dep) u = ST.fa[u][p];
        if (u == v) return u;
        for (int p = logN; p >= 0; p--) if (ST.fa[u][p] != ST.fa[v][p]) u = ST.fa[u][p], v = ST.fa[v][p];
        return ST.fa[u][0];
    }

    void mian() {
        std::cin >> u >> v;
        int lca = LCA(u, v);
        int ans = 0;
        ans = std::max(ans, ST.QueryUp(u, lca));
        ans = std::max(ans, ST.QueryDw(v, lca));
        ans = std::max(ans, ST.QueryMx(v, lca) - ST.QueryMn(u, lca));
        std::cout << ans << '\n';
        return;
    }
}

int main() {
    std::cin >> N;
    for (int i = 1; i <= N; i++) std::cin >> w[i];
    for (int i = 1; i < N; i++) std::cin >> u >> v, graph::addEdge(u, v), graph::addEdge(v, u);
    graph::DFS(1, 0);
    std::cin >> Q;
    while (Q--) graph::mian();
    return 0;
}