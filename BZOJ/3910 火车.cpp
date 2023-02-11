#include <iostream>
#include <cmath>

typedef long long lxl;

const int maxN = 5e5;
const int maxM = 4e5;
const int logN = 19;

int n, m, a;
int x, y;
int t[maxM + 10];

namespace graph {
    struct Vertex {
        int head;
        int from;
        int dep;
        int tag;
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
        int f[maxN + 10][logN + 5];

        void Init() {
            for (int u = 1; u <= n; u++) {
                f[u][0] = vertex[u].from;
            }
            for (int p = 1; p <= logN; p++) {
                for (int u = 1; u <= n; u++) {
                    f[u][p] = f[f[u][p - 1]][p - 1];
                }
            }
            return;
        }
    } ST;

    struct DisjointSetUnion {
        struct Node {
            int fa;
        } node[maxN + 10];

        void init() {
            for (int u = 1; u <= n; u++) {
                if (vertex[u].tag) node[u].fa = vertex[u].from;
                else node[u].fa = u;
            }
            return;
        }

        int Find(int u) {
            if (node[u].fa == u) return u;
            return node[u].fa = Find(node[u].fa);
        }

        void Union(int u, int v) {
            u = Find(u);
            v = Find(v);
            if (u == v) return;
            node[u].fa = v;
            return;
        }
    } DSU;

    void DFS(int u, int from) {
        //printf("DFS(%d, %d)\n", u, from);
        vertex[u].from = from;
        vertex[u].dep = vertex[from].dep + 1;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            DFS(v, u);
        }
        return;
    }

    int LCA(int u, int v) {
        if (vertex[u].dep < vertex[v].dep) std::swap(u, v);
        int dif = vertex[u].dep - vertex[v].dep;
        for (int p = logN; p >= 0; p--) {
            if (vertex[ST.f[u][p]].dep >= vertex[v].dep) {
                u = ST.f[u][p];
            }
        }
        if (u == v) return u;
        for (int p = logN; p >= 0; p--) {
            if (ST.f[u][p] != ST.f[v][p]) {
                u = ST.f[u][p];
                v = ST.f[v][p];
            }
        }
        return ST.f[u][0];
    }

    void PushUp(int u, int v) {
        if (vertex[u].dep < vertex[v].dep) return;
        //printf("PushUp(%d, %d)\n", u, v);
        vertex[u].tag = true;
        DSU.Union(u, ST.f[u][0]);
        PushUp(DSU.Find(ST.f[u][0]), v);
        return;
    }
}

lxl ans;

int main() {
    //freopen("1.in", "r", stdin);
    //freopen("1.out", "w", stdout);
    std::cin >> n >> m >> a;
    for (int i = 1; i < n; i++) {
        std::cin >> x >> y;
        graph::addEdge(x, y);
        graph::addEdge(y, x);
    }
    for (int i = 1; i <= n; i++) graph::vertex[i].tag = true;
    for (int i = 1; i <= m; i++) std::cin >> t[i], graph::vertex[t[i]].tag = false;
    graph::DFS(1, 0);
    graph::ST.Init();
    graph::DSU.init();
    for (int i = 1; i <= m; i++) {
        if (graph::vertex[t[i]].tag) continue;
        int lca = graph::LCA(a, t[i]);
        ans += graph::vertex[a].dep + graph::vertex[t[i]].dep - 2 * graph::vertex[lca].dep;
        graph::PushUp(a, lca);
        graph::PushUp(t[i], lca);
        a = t[i];
    }
    std::cout << ans;
    return 0;
}