#include <iostream>

typedef long long lxl;

const int maxN = 1e5;

int n;
int u, v, w;

namespace graph {
    struct Vertex {
        int head;
        lxl dep;

        Vertex() {
            head = -1;
            return;
        }
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
        int weight;
    } edge[2 * maxN + 10];

    int ecnt;

    void addEdge(int tail, int head, int weight) {
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        edge[ecnt].weight = weight;
        vertex[tail].head = ecnt;
        ecnt++;
        return;
    }

    void DFS(int u, int from) {
        for (int e = vertex[u].head; ~e; e = edge[e].next) {
            int v = edge[e].head;
            int w = edge[e].weight;
            if (v == from) continue;
            vertex[v].dep = vertex[u].dep + w;
            DFS(v, u);
        }
        return;
    }
}

int main() {
    std::cin >> n;
    for (int i = 1; i < n; i++) {
        std::cin >> u >> v >> w;
        graph::addEdge(u, v, w);
        graph::addEdge(v, u, w);
    }
    graph::DFS(1, 0);
    for (int i = 1; i <= n; i++) std::cout << (graph::vertex[i].dep & 1) << '\n';
    return 0;
}