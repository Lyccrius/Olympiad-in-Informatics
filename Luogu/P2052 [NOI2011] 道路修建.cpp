#include <iostream>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef long long lxl;

const int maxN = 1e6;
const int maxC = 1e6;

int n;
int a, b, c;
lxl ans;

namespace graph {
    struct Vertex {
        int head;
        int size;
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
        lxl weight;
    } edge[maxN * 2 + 10];

    int ecnt;

    void addEdge(int tail, int head, int weight) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].weight = weight;
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
            vertex[u].size += vertex[v].size;
            ans += edge[e].weight * std::abs(vertex[v].size * 2 - n);
        }
        return;
    }
}

int main() {
    std::cin >> n;
    for (int i = 1; i < n; i++) std::cin >> a >> b >> c, graph::addEdge(a, b, c), graph::addEdge(b, a, c);
    graph::DFS(1, 0);
    std::cout << ans << '\n';
    return 0;
}