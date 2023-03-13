#include <iostream>
#include <algorithm>

typedef long long lxl;

const int maxN = 2e5;

int n;
int a[maxN + 10];
int u, v;
lxl A;
lxl ans;

namespace graph {
    struct Vertex {
        int head;
        lxl size;
        int dep;
        lxl res;
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

    void DFS(int u, int from, int dep) {
        vertex[u].size = a[u];
        vertex[u].dep = dep;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            DFS(v, u, dep + 1);
            vertex[u].size += vertex[v].size;
        }
        return;
    }

    void mian() {
        for (int i = 1; i <= n; i++) vertex[1].res += 1ll * vertex[i].dep * a[i];
        return;
    }

    void DP(int u, int from) {
        if (u != 1) vertex[u].res = vertex[from].res + A - vertex[u].size - vertex[u].size;
        ans = std::max(ans, vertex[u].res);
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            DP(v, u);
        }
        return;
    }
}

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i], A += a[i];
    for (int i = 1; i < n; i++) std::cin >> u >> v, graph::addEdge(u, v), graph::addEdge(v, u);
    graph::DFS(1, 0, 0);
    graph::mian();
    graph::DP(1, 0);
    std::cout << ans;
    return 0;
}