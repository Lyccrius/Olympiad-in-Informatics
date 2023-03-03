#include <iostream>
#include <algorithm>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef long long lxl;

const int maxN = 1e6;

int n;
int u, v;
int ans;

namespace graph {
    struct Vertex {
        int head;
        int size;
        int dep;
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
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            vertex[v].size = 1;
            vertex[v].dep = vertex[u].dep + 1;
            DFS(v, u);
            vertex[u].size += vertex[v].size;
        }
        return;
    }
    
    lxl f[maxN + 10];

    void DP(int u, int from) {
        if (f[ans] < f[u]) ans = u;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            f[v] = f[u] - vertex[v].size + (n - vertex[v].size);
            DP(v, u);
        }
        return;
    }
}

int main() {
    promote();
    std::cin >> n;
    for (int i = 1; i < n; i++) {
        std::cin >> u >> v;
        graph::addEdge(u, v);
        graph::addEdge(v, u);
    }
    graph::DFS(1, 0);
    for (int i = 1; i <= n; i++) graph::f[1] += graph::vertex[u].dep;
    graph::DP(1, 0);
    std::cout << ans;
    return 0;
}