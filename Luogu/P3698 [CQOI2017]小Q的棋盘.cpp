#include <iostream>

const int maxN = 100;
const int maxV = 100;

int V, N;
int a, b;
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

    void DFS(int u, int from) {
        //printf("DFS %d from %d\n", u, from);
        for (int i = 0; i <= N; i++) vertex[u].f[i] = 1;
        for (int i = 0; i <= N; i++) vertex[u].g[i] = 1;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            DFS(v, u);
        }
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            for (int i = N; i >= 0; i--) {
                for (int j = 0; j <= i - 1; j++) {
                    vertex[u].g[i] = std::max(vertex[u].g[i], vertex[u].f[i - j - 1] + vertex[v].g[j]);
                    vertex[u].g[i] = std::max(vertex[u].g[i], vertex[u].f[i - j - 1] + vertex[v].f[j]);
                    vertex[u].g[i] = std::max(vertex[u].g[i], vertex[u].g[i - j - 2] + vertex[v].f[j]);
                }
            }
            for (int i = N; i >= 0; i--) {
                for (int j = 0; j <= i - 2; j++) {
                    vertex[u].f[i] = std::max(vertex[u].f[i], vertex[u].f[i - j - 2] + vertex[v].f[j]);
                }
            }
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
    graph::DFS(0, 0);
    std::cout << std::max(graph::vertex[0].f[N], graph::vertex[0].g[N]) << '\n';
    return 0;
}