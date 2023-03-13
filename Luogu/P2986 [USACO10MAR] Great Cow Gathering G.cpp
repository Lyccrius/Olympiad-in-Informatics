#include <iostream>
#include <algorithm>

typedef long long lxl;

const int maxN = 1e5;
const lxl inf = 1e18;

int n;
int c[maxN + 10];
int a[maxN + 10], b[maxN + 10], l[maxN + 10];
lxl C;
lxl ans = inf;

namespace graph {
    struct Vertex {
        int head;
        lxl size;
        lxl res;
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
        int weight;
    } edge[maxN * 2 + 10];

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
        vertex[u].size = c[u];
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            int w = edge[e].weight;
            if (v == from) continue;
            DFS(v, u);
            vertex[u].size += vertex[v].size;
            vertex[u].res += vertex[v].size * w;
            vertex[u].res += vertex[v].res;
        }
        return;
    }

    void DP(int u, int from) {
        ans = std::min(ans, vertex[u].res);
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            int w = edge[e].weight;
            if (v == from) continue;
            vertex[v].res = vertex[u].res + 1ll * (C - vertex[v].size - vertex[v].size) * w;
            DP(v, u);
        }
        return;
    }
}

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> c[i], C += c[i];
    for (int i = 1; i < n; i++) std::cin >> a[i] >> b[i] >> l[i], graph::addEdge(a[i], b[i], l[i]), graph::addEdge(b[i], a[i], l[i]);
    graph::DFS(1, 0);
    graph::DP(1, 0);
    std::cout << ans;
    return 0;
}