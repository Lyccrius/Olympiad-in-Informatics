#include <iostream>

const int maxN = 1000;

int n;
int u, v, w;

namespace graph {
    struct Vertex {
        int head;
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
        int weight;
    } edge[2 * maxN + 10];

    int ecnt;

    int dis[maxN + 10][maxN + 10];

    void addEdge(int tail, int head, int weight) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        edge[ecnt].weight = weight;
        vertex[tail].head = ecnt;
        return;
    }

    void DFS(int top, int u, int from) {
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            int w = edge[e].weight;
            if (v == from) continue;
            dis[top][v] = dis[top][u] + w;
            DFS(top, v, u);
        }
        return;
    }
}

int main() {
    std::cin >> n;
    std::cout << n << '\n';
    for (int i = 1; i < n; i++) {
        std::cin >> u >> v >> w;
        graph::addEdge(u, v, w);
        graph::addEdge(v, u, w);
    }
    for (int i = 1; i <= n; i++) graph::DFS(i, i, 0);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            std::cout << graph::dis[i][j] << ' ';
        }
        std::cout << '\n';
    }
    return 0;
}