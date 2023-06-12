#include <iostream>

typedef long long lxl;

const int maxN = 2e5;

int n;
int u, v;

namespace graph {
    struct Vertex {
        int head;
        int size;
        int dep;
        lxl res;
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
    } edge[2 * maxN + 10];

    int ecnt;

    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    void DFS0(int u, int from) {
        vertex[u].size = 1;
        vertex[1].res += vertex[u].dep;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            vertex[v].dep = vertex[u].dep + 1;
            DFS0(v, u);
            vertex[u].size += vertex[v].size;
        }
        return;
    }

    void DFS1(int u, int from) {
        if (u != 1) vertex[u].res = vertex[from].res + n - 2 * vertex[u].size;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            DFS1(v, u);
        }
        return;
    }
}

int main() {
    std::cin >> n;
    for (int i = 1; i <= n - 1; i++) std::cin >> u >> v, graph::addEdge(u, v), graph::addEdge(v, u);
    graph::DFS0(1, 0);
    graph::DFS1(1, 0);
    for (int i = 1; i <= n; i++) std::cout << graph::vertex[i].res << '\n';
    return 0;
}