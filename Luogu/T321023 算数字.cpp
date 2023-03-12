#include <iostream>

typedef long long lxl;

const int mod = 998244353;

const int maxN = 3e5;

int n;
int u, v;
lxl S;

namespace graph {
    struct Vertex {
        int head;
        lxl size;
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
            DFS(v, u);
            vertex[u].size = (1ll * vertex[u].size + vertex[v].size) % mod;
        }
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            S = (1ll * S + 1ll * (vertex[u].size - vertex[v].size) * vertex[v].size % mod * u % mod) % mod;
        }
        S = (1ll * S + 1ll * vertex[u].size * u % mod * u % mod * 2 % mod) % mod;
        S = (1ll * S + 1ll * u * u % mod * u % mod) % mod;
        vertex[u].size = (1ll * vertex[u].size + u) % mod; 
        return;
    }
}

int main() {
    std::cin >> n;
    for (int i = 1; i < n; i++) std::cin >> u >> v, graph::addEdge(u, v), graph::addEdge(v, u);
    graph::DFS(1, 0);
    std::cout << (S % mod + mod) % mod;
    return 0;
}