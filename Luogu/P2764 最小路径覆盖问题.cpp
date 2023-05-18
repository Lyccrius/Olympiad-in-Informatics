#include <iostream>

const int maxN = 150;
const int maxM = 6000;

int n, m;
int u, v;

namespace graph {
    struct Vertex {
        int vis;
        int head;
        int match;
    } vertex[2 * maxN + 10];

    struct Edge {
        int head;
        int next;
    } edge[maxM + 10];

    int ecnt;

    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    bool DFS(int u, int t) {
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (vertex[v].vis == t) continue;
            vertex[v].vis = t;
            if (vertex[v].match == 0 || DFS(vertex[v].match, t)) {
                vertex[v].match = u;
                vertex[u].match = v;
                return true;
            }
        }
        return false;
    }
}

void print(int u) {
    while (u != - n) {
        std::cout << u << ' ';
        u = graph::vertex[u].match - n;
    }
    std::cout << '\n';
    return;
}

int main() {
    int matched = 0;
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) std::cin >> u >> v, graph::addEdge(u, n + v);
    for (int i = 1; i <= n; i++) if (graph::DFS(i, i)) matched++;
    for (int i = 1; i <= n; i++) if (graph::vertex[i + n].match == 0) print(i);
    std::cout << n - matched << '\n';
    return 0;
}