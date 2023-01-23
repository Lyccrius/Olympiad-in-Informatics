#include <iostream>
#include <cstring>

typedef long long lxl;

const int maxN = 5000;

int n;
int f[maxN + 10];
int u, v;
lxl g[maxN + 10][maxN + 10];

namespace graph {
    struct Vertex {
        int head;
        int size;
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
        vertex[u].size = 1;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            DFS(v, u);
            for (int j = vertex[u].size - 1; j >= 0; j--) {
                for (int k = vertex[v].size - 1; k >= 0; k--) {
                    g[u][j + k] = std::min(g[u][j + k], g[u][j] + g[v][k]);
                }
            }
            vertex[u].size += vertex[v].size;
        }
        for (int i = 0; i <= vertex[u].size - 1; i++) {
            g[u][vertex[u].size - 1] = std::min(g[u][vertex[u].size - 1], g[u][i] + f[vertex[u].size - i]);
        }
        return;
    }
}

int main() {
    std::memset(g, 0x3f, sizeof(g));
    std::cin >> n;
    for (int i = 2; i <= n; i++) std::cin >> f[i];
    for (int i = 2; i <= n; i++) std::cin >> u >> v, graph::addEdge(u, v), graph::addEdge(v, u);
    for (int i = 1; i <= n; i++) g[i][0] = 0;
    graph::DFS(1, 0);
    std::cout << g[1][graph::vertex[1].size - 1];
    return 0;
}