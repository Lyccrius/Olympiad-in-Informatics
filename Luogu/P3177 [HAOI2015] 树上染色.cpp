#include <iostream>
#include <algorithm>

typedef long long lxl;

const int maxN = 2000;
const int maxK = 2000;
const lxl inf = 1e9 + 10;

int n, k;
int u, v, w;

namespace graph {
    struct Vertex {
        int head;
        int size;
        lxl f[maxK + 10];
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
        int weight;
    } edge[2 * maxN + 10];

    int ecnt;

    void addEdge(int tail, int head, int weight) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        edge[ecnt].weight = weight;
        vertex[tail].head = ecnt;
        return;
    }

    void DFS(int u, int from) {
        //std::fill(vertex[u].f, vertex[u].f + k + 1, -inf);
        for (int i = 0; i <= k; i++) vertex[u].f[i] = -inf;
        vertex[u].f[0] = 0;
        vertex[u].f[1] = 0;
        vertex[u].size = 1;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            DFS(v, u);
            vertex[u].size += vertex[v].size;
        }
        //printf("size[%d] = %d\n", u, vertex[u].size);
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            int w = edge[e].weight;
            if (v == from) continue;
            for (int i = std::min(k, vertex[u].size); i >= 0; i--) {
                for (int j = 0; j <= std::min(i, vertex[v].size); j++) {
                    lxl h = 1ll * j * (k - j) * w;
                    lxl b = 1ll * (vertex[v].size - j) * (n - k + j - vertex[v].size) * w;
                    vertex[u].f[i] = std::max(vertex[u].f[i], vertex[u].f[i - j] + vertex[v].f[j] + h + b);
                }
            }
        }
        for (int i = 0; i <= k; i++) {
            //printf("f[%d][%d] = %lld\n", u, i, vertex[u].f[i]);
        }
        return;
    }
}

int main() {
    std::cin >> n >> k;
    for (int i = 1; i < n; i++) {
        std::cin >> u >> v >> w;
        graph::addEdge(u, v, w);
        graph::addEdge(v, u, w);
    }
    graph::DFS(1, 0);
    std::cout << graph::vertex[1].f[k] << '\n';
    return 0;
}