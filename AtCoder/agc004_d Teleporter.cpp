#include <iostream>

const int maxN = 1e5;

int n, k;
int a[maxN + 10];
int c;

namespace graph {
    struct Vertex {
        int head;
        int dis;
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
    } edge[maxN + 10];

    int ecnt;

    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    void DFS(int u, int from) {
        if (vertex[u].dis > k) {
            vertex[u].dis = 1;
            c++;
        }
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            vertex[v].dis = vertex[u].dis + 1;
            DFS(v, u);
        }
        return;
    }
}

int main() {
    std::cin >> n >> k;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 2; i <= n; i++) graph::addEdge(a[i], i);
    graph::DFS(1, 0);
    if (a[1] != 1) c++;
    std::cout << c << '\n';
    return 0;
}