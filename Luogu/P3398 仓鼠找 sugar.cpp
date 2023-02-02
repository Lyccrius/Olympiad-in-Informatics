#include <iostream>

const int maxN = 1e5;
const int maxQ = 1e5;
const int logN = 17;

int n, q;
int u, v;
int a, b, c, d;

namespace graph {
    struct Vertex {
        int head;
        int dep;
        int fa[logN + 5];
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

    void DFS(int u, int from) {
        vertex[u].dep = vertex[from].dep + 1;
        vertex[u].fa[0] = from;
        for (int p = 1; p <= logN; p++) vertex[u].fa[p] = vertex[vertex[u].fa[p - 1]].fa[p - 1];
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            DFS(v, u);
        }
        return;
    }

    int LCA(int u, int v) {
        if (vertex[u].dep < vertex[v].dep) std::swap(u, v);
        for (int p = logN; p >= 0; p--) if (vertex[vertex[u].fa[p]].dep >= vertex[v].dep) u = vertex[u].fa[p];
        if (u == v) return u;
        for (int p = logN; p >= 0; p--) if (vertex[u].fa[p] != vertex[v].fa[p]) u = vertex[u].fa[p], v = vertex[v].fa[p];
        return vertex[u].fa[0];
    }

    void mian() {
        std::cin >> a >> b >> c >> d;
        int ab = LCA(a, b);
        int cd = LCA(c, d);
        //printf("ab = %d, cd = %d\n", ab, cd);
        int abcd = LCA(ab, cd);
        if (vertex[ab].dep < vertex[cd].dep) {
            std::swap(ab, cd);
            std::swap(a, c);
            std::swap(b, d);
        }
        if (LCA(ab, c) == ab || LCA(ab, d) == ab) std::cout << "Y\n";
        else std::cout << "N\n";
        return;
    }
}

int main() {
    std::cin >> n >> q;
    for (int i = 1; i < n; i++) std::cin >> u >> v, graph::addEdge(u, v), graph::addEdge(v, u);
    graph::DFS(1, 0);
    while (q--) graph::mian();
    return 0;
}