#include <iostream>

const int maxN = 200;

int n;
int a[maxN + 10], b[maxN + 10];
int ban;
int ans;

namespace graph {
    struct Vertex {
        int head;
        int link;
        int dia;
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

    int DFS(int u, int from) {
        vertex[u].dia = 0;
        vertex[u].link = 0;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            DFS(v, u);
            vertex[u].dia = std::max(vertex[u].dia, vertex[v].dia);
            vertex[u].dia = std::max(vertex[u].dia, vertex[u].link + vertex[v].link + 1);
            vertex[u].link = std::max(vertex[u].link, vertex[v].link + 1);
        }
        return vertex[u].dia;
    }
}

int main() {
    std::cin >> n;
    for (int i = 1; i < n; i++) std::cin >> a[i] >> b[i], graph::addEdge(a[i], b[i]), graph::addEdge(b[i], a[i]);
    for (int i = 1; i < n; i++) ans = std::max(ans, graph::DFS(a[i], b[i]) * graph::DFS(b[i], a[i]));
    std::cout << ans;
    return 0;
}