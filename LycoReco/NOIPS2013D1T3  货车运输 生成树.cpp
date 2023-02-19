#include <iostream>
#include <algorithm>
#include <vector>

const int maxN = 1e4;
const int maxM = 5e4;
const int maxQ = 3e4;
const int maxZ = 1e5;

int n, m;
int x, y, z;
int q;

namespace graph {
    struct Vertex {
        int dep;
        int head;
        int from;
        int weight;
    } vertex[maxN + 10];

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

    void addEdge(int tail, int head, int weight) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        edge[ecnt].weight = weight;
        vertex[tail].head = ecnt;
        return;
    }

    std::vector<Edge> edges;

    struct DisjointSetUnion {
        struct Node {
            int fa;
        } node[maxN + 10];

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

    void DFS(int u, int from) {
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            int w = edge[e].weight;
            if (v == from) continue;
            vertex[v].dep = vertex[u].dep + 1;
            vertex[v].from = u;
            vertex[v].weight = w;
            DFS(v, u);
        }
        return;
    }

    void Kruscal() {
        DSU.Init();
        std::sort(edges.begin(), edges.end());
        for (auto e : edges) {
            int u = e.tail;
            int v = e.head;
            int w = e.weight;
            int fu = DSU.Find(u);
            int fv = DSU.Find(v);
            if (fu == fv) continue;
            DSU.Union(fu, fv);
            addEdge(u, v, w);
            addEdge(v, u, w);
        }
        for (int u = 1; u <= n; u++) {
            if (!vertex[u].dep) {
                DFS(u, 0);
            }
        }
        return;
    }

    int LCA(int u, int v) {
        int ret = maxZ;
        if (vertex[u].dep < vertex[v].dep) std::swap(u, v);
        while (vertex[u].dep > vertex[v].dep) {
            ret = std::min(ret, vertex[u].weight);
            u = vertex[u].from;
        }
        while (u != v) {
            ret = std::min(ret, vertex[u].weight);
            ret = std::min(ret, vertex[v].weight);
            u = vertex[u].from;
            v = vertex[v].from;
        }
        return ret;
    }

    int query(int u, int v) {
        int fu = DSU.Find(u);
        int fv = DSU.Find(v);
        if (fu != fv) return -1;
        return LCA(u, v);
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
    graph::Kruscal();
    std::cin >> q;
    while (q--) mian();
    return 0;
}