#include <iostream>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 3e5;
const int maxM = 3e5;
const int maxQ = 3e5;

int n, m, q;
int u, v;
int x, y;
int opt;

namespace graph {
    struct Vertex {
        int head;
        int diam;
        int link;

        Vertex() {
            head = -1;
            return;
        }
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
    } edge[2 * maxM + 10];

    int ecnt;

    void addEdge(int tail, int head) {
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        ecnt++;
        return;
    }

    struct DisjointSetUnion {
        struct Node {
            int fa;
            int res;
        } node[maxN + 10];

        void Init() {
            for (int i = 1; i <= n; i++) node[i].fa = i;
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
            node[v].res = std::max(node[v].res, (node[u].res + 1) / 2 + (node[v].res + 1) / 2 + 1);
            node[v].res = std::max(node[v].res, node[u].res);
            return;
        }

        int Query(int u) {
            u = Find(u);
            return node[u].res;
        }
    } DSU;

    void DFS(int u, int from) {
        for (int e = vertex[u].head; ~e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            DFS(v, u);
            vertex[u].diam = std::max(vertex[u].diam, vertex[v].diam);
            vertex[u].diam = std::max(vertex[u].diam, vertex[v].link + 1 + vertex[u].link);
            vertex[u].link = std::max(vertex[u].link, vertex[v].link + 1);
        }
        return;
    }
}

int main() {
    promote();
    std::cin >> n >> m >> q;
    graph::DSU.Init();
    for (int i = 1; i <= m; i++) {
        std::cin >> u >> v;
        graph::addEdge(u, v);
        graph::addEdge(v, u);
        graph::DSU.Union(u, v);
    }
    for (int i = 1; i <= n; i++) {
        if (graph::DSU.Find(i) == i) {
            graph::DFS(i, 0);
            graph::DSU.node[i].res = graph::vertex[i].diam;
        }
    }
    for (int i = 1; i <= q; i++) {
        std::cin >> opt;
        if (opt == 1) {
            std::cin >> x;
            std::cout << graph::DSU.Query(x) << '\n';
        } else if (opt == 2) {
            std::cin >> x >> y;
            graph::DSU.Union(x, y);
        }
    }
    return 0;
}