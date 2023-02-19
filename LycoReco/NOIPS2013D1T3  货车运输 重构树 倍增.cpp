#include <iostream>
#include <algorithm>
#include <vector>

const int maxN = 1e4;
const int maxM = 5e4;
const int maxQ = 3e4;
const int maxZ = 1e5;
const int logN = 13;

int n, m;
int x, y, z;
int q;

namespace graph {
    struct Vertex {
        int dep;
        int head;
        int weight;
    } vertex[maxN * 2 + 10];

    int vcnt;

    struct Edge {
        int tail;
        int head;
        int next;
        int weight;

        bool operator<(const Edge &other) const {
            return weight > other.weight;
        }
    } edge[maxN * 2 + 10];

    int ecnt;

    std::vector<Edge> edges;

    struct DisjointSetUnion {
        struct Node {
            int fa;
        } node[maxN * 2 + 10];

        void Init() {
            for (int u = 1; u <= n; u++) node[u].fa = u;
            return;
        }

        int Find(int u) {
            if (node[u].fa == u) return u;
            return node[u].fa = Find(node[u].fa);
        }

        void Union(int u, int v) {
            int fu = Find(u);
            int fv = Find(v);
            if (fu == fv) return;
            node[fu].fa = fv;
            return;
        }
    } DSU;

    struct SparseTable {
        struct Node {
            int f;
        } node[maxN * 2 + 10][logN + 1 + 5];
    } ST;

    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    void addVertex(int u, int v, int w) {
        vcnt++;
        vertex[vcnt].weight = w;
        addEdge(vcnt, u);
        addEdge(vcnt, v);
        DSU.node[vcnt].fa = vcnt;
        DSU.Union(u, vcnt);
        DSU.Union(v, vcnt);
        return;
    }

    void init() {
        DSU.Init();
        vcnt = n;
        return;
    }

    void DFS(int u, int from) {
        for (int p = 1; p <= logN + 1; p++) {
            ST.node[u][p].f = ST.node[ST.node[u][p - 1].f][p - 1].f;
        }
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            ST.node[v][0].f = u;
            vertex[v].dep = vertex[u].dep + 1;
            DFS(v, u);
        }
        return;
    }

    void Kruscal() {
        int cnt = 0;
        std::sort(edges.begin(), edges.end());
        for (auto e : edges) {
            int u = e.tail;
            int v = e.head;
            int w = e.weight;
            int fu = DSU.Find(u);
            int fv = DSU.Find(v);
            if (fu == fv) continue;
            addVertex(fu, fv, w);
            cnt++;
            if (cnt == n - 1) break;
        }
        for (int u = vcnt; u > n; u--) {
            if (!vertex[u].dep) {
                DFS(u, 0);
            }
        }
        return;
    }

    int LCA(int u, int v) {
        if (vertex[u].dep < vertex[v].dep) std::swap(u, v);
        for (int p = logN + 1; p >= 0; p--) {
            if (ST.node[u][p].f && vertex[ST.node[u][p].f].dep >= vertex[v].dep) {
                u = ST.node[u][p].f;
            }
        }
        if (u == v) return u;
        for (int p = logN + 1; p >= 0; p--) {
            if (ST.node[u][p].f != ST.node[v][p].f) {
                u = ST.node[u][p].f;
                v = ST.node[v][p].f;
            }
        }
        return ST.node[u][0].f;
    }

    int query(int u, int v) {
        int fu = DSU.Find(u);
        int fv = DSU.Find(v);
        if (fu != fv) return -1;
        return vertex[LCA(u, v)].weight;
    }
}

void mian() {
    std::cin >> x >> y;
    std::cout << graph::query(x, y) << '\n';
    return;
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        std::cin >> x >> y >> z;
        graph::edges.push_back((graph::Edge) {x, y, 0, z});
    }
    graph::init();
    graph::Kruscal();
    std::cin >> q;
    while (q--) mian();
    return 0;
}