#include <iostream>

const int maxN = 1e5;
const int maxM = 2e5;

int n, m;
int u, v;

namespace graph {
    struct Vertex {
        int head;
        int vis;
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

    void mian() {
        int ans = 0;
        for (int u = 1; u <= n; u++) {
            for (int e = vertex[u].head; e; e = edge[e].next) {
                int v = edge[e].head;
                vertex[v].vis = u;
            }
            for (int eu = vertex[u].head; eu; eu = edge[eu].next) {
                int v = edge[eu].head;
                for (int ev = vertex[v].head; ev; ev = edge[ev].next) {
                    int w = edge[ev].head;
                    if (vertex[w].vis == u) ans++;
                }
            }
        }
        std::cout << ans / 6;
        return;
    }
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        std::cin >> u >> v;
        //if (u > v) std::swap(u, v);
        graph::addEdge(u, v);
        graph::addEdge(v, u);
    }
    graph::mian();
    return 0;
}