#include <iostream>

const int maxN = 100;
const int maxV = 100;

int V, N;
int a, b;
int res;
int ans;

namespace graph {
    struct Vertex {
        int head;
        int f[maxN + 10];
        int g[maxN + 10];
    } vertex[maxV + 10];

    struct Edge {
        int head;
        int next;
    } edge[2 * maxV + 10];

    int ecnt;

    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    void DFS(int u, int from, int dep) {
        res = std::max(res, dep);
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            DFS(v, u, dep + 1);
        }
        return;
    }
}

int main() {
    std::cin >> V >> N;
    for (int i = 1; i < V; i++) {
        std::cin >> a >> b;
        graph::addEdge(a, b);
        graph::addEdge(b, a);
    }
    graph::DFS(0, 0, 0);
    if (N <= res) {
        std::cout << N + 1 << '\n';
    } else {
        std::cout << std::min(V, res + (N - res) / 2 + 1);
    }
    return 0;
}