#include <iostream>

const int maxN = 100;
const int maxV = 100;

int V, N;
int a, b;

namespace graph {
    struct Vertex {
        int head;
        int f[maxN + 10];
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
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            DFS(v, u);
            for (int i = N; i >= 0; i--) {
                //vertex[u].f[i] = 1;
                for (int j = 0; j < i; j++) {
                    vertex[u].f[i] = std::max(vertex[u].f[i], vertex[u].f[i - j - 1] + vertex[v].f[j]);
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
    std::cout << graph::vertex[0].f[N] << '\n';
    return 0;
}