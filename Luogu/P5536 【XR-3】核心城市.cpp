#include <iostream>
#include <queue>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 1e5;

int n, k;
int u, v;
int p;

namespace tree {
    struct Vertex {
        int head;
        int dep;
        int from;
        int height;

        bool operator<(const Vertex &other) const {
            return height < other.height;
        }
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
        vertex[u].from = from;
        vertex[u].height = 1;
        if (vertex[u].dep > vertex[p].dep) p = u;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            vertex[v].dep = vertex[u].dep + 1;
            DFS(v, u);
            vertex[u].height = std::max(vertex[u].height, vertex[v].height + 1);
        }
        return;
    }

    void mian() {
        vertex[1].dep = 0; DFS(1, 0);
        vertex[p].dep = 0; DFS(p, 0);
        int m = vertex[p].dep / 2;
        for (int i = 1; i <= m; i++) p = vertex[p].from;
        vertex[p].dep = 0; DFS(p, 0);
        std::priority_queue<Vertex> q;
        for (int i = 1; i <= n; i++) q.push(vertex[i]);
        for (int i = 1; i <= k; i++) q.pop();
        std::cout << q.top().height;
        return;
    }
}

int main() {
    promote();
    std::cin >> n >> k;
    for (int i = 1; i < n; i++) std::cin >> u >> v, tree::addEdge(u, v), tree::addEdge(v, u);
    tree::mian();
    return 0;
}