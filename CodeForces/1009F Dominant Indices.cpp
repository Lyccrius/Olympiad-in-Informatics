#include <iostream>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 1e6;

int n;
int u, v;
int f[maxN + 10];
int *t = f;

namespace graph {
    struct Vertex {
        int height;
        int head;
        int hson;
        int ans;
        int *f;
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
    } edge[2 * maxN + 10];

    int ecnt;

    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    void DFS0(int u, int from) {
        vertex[u].height = 1;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            DFS0(v, u);
            if (vertex[u].height < vertex[v].height + 1) {
                vertex[u].height = vertex[v].height + 1;
                vertex[u].hson = v;
            }
        }
        return;
    }

    void DFS1(int u, int from) {
        vertex[u].f[0] = 1;
        if (vertex[u].hson) {
            vertex[vertex[u].hson].f = vertex[u].f + 1;
            DFS1(vertex[u].hson, u);
            vertex[u].ans = vertex[vertex[u].hson].ans + 1;
        }
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            if (v == vertex[u].hson) continue;
            vertex[v].f = t; t += vertex[v].height;
            DFS1(v, u);
            for (int i = 1; i <= vertex[v].height; i++) {
                vertex[u].f[i] += vertex[v].f[i - 1];
                if (vertex[u].f[i] > vertex[u].f[vertex[u].ans]) vertex[u].ans = i;
                if (vertex[u].f[i] == vertex[u].f[vertex[u].ans] && i < vertex[u].ans) vertex[u].ans = i;
            }
        }
        if (vertex[u].f[vertex[u].ans] == 1) vertex[u].ans = 0;
        return;
    }
}

int main() {
    promote();
    std::cin >> n;
    for (int i = 1; i <= n - 1; i++) std::cin >> u >> v, graph::addEdge(u, v), graph::addEdge(v, u);
    graph::DFS0(1, 0);
    graph::vertex[1].f = t;
    t += graph::vertex[1].height;
    graph::DFS1(1, 0);
    for (int i = 1; i <= n; i++) std::cout << graph::vertex[i].ans << '\n';
    return 0;
}