#include <iostream>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef long long lxl;

const int maxN = 1e6;

int N, M;
int B[maxN + 10], C[maxN + 10];
int L[maxN + 10];

lxl ans;

struct Heap {
    struct Node {
        int lson;
        int rson;
        int dist;
        lxl size;
        lxl cost;
        int weight;
    } node[maxN + 10];

    int ncnt;
    int root[maxN + 10];

    void PushUp(int u) {
        node[u].size = node[node[u].lson].size + node[node[u].rson].size + 1;
        node[u].cost = node[node[u].lson].cost + node[node[u].rson].cost + node[u].weight;
        return;
    }

    void Insert(int &u, int w) {
        if (!u) u = ++ncnt;
        node[u].weight = w;
        node[u].cost = w;
        node[u].size = 1;
        return;
    }

    int Merge(int u, int v) {
        if (!u || !v) return u + v;
        if (node[u].weight < node[v].weight) std::swap(u, v);
        node[u].rson = Merge(node[u].rson, v);
        PushUp(u);
        if (node[node[u].lson].dist < node[node[u].rson].dist) std::swap(node[u].lson, node[u].rson);
        node[u].dist = node[node[u].rson].dist + 1;
        return u;
    }

    void Pop(int &u) {
        u = Merge(node[u].lson, node[u].rson);
        return;
    }
} H;

namespace graph {
    struct Vertex {
        int head;
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
    } edge[maxN * 4 + 10];

    int ecnt;

    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    void DFS(int u) {
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            DFS(v);
            H.root[u] = H.Merge(H.root[u], H.root[v]);
        }
        while (H.root[u] && H.node[H.root[u]].size && H.node[H.root[u]].cost > M) H.Pop(H.root[u]);
        ans = std::max(ans, H.node[H.root[u]].size * L[u]);
        return;
    }
}

int main() {
    std::cin >> N >> M;
    for (int i = 1; i <= N; i++) std::cin >> B[i] >> C[i] >> L[i];
    for (int i = 1; i <= N; i++) if (B[i]) graph::addEdge(B[i], i);
    for (int i = 1; i <= N; i++) H.Insert(H.root[i], C[i]);
    graph::DFS(1);
    std::cout << ans << '\n';
    return 0;
}