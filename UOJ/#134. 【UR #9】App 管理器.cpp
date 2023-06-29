#include <iostream>

const int maxN = 5000;
const int maxM = 5000;

int n, m;
int a[maxM + 10], b[maxM + 10], t[maxM + 10];

namespace graph {
    struct Vertex {
        int head;
        int vis;
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
        int del;
    } edge[2 * maxM + 10];

    int ecnt = 1;
    
    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    void DFS(int u) {
        vertex[u].vis = true;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (edge[e].del) continue;
            if (vertex[v].vis) continue;
            DFS(v);
        }
        return;
    }
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) std::cin >> a[i] >> b[i] >> t[i], graph::addEdge(a[i], b[i]), graph::addEdge(b[i], a[i]);
    for (int i = 1; i <= m; i++) if (t[i]) graph::edge[2 * i + 1].del = true;
    for (int i = 1; i <= m; i++) {
        if (t[i]) {
            std::cout << 0 << '\n';
            continue;
        }
        for (int i = 1; i <= n; i++) graph::vertex[i].vis = false;
        graph::edge[2 * i].del = true;
        graph::edge[2 * i + 1].del = true;
        graph::DFS(b[i]);
        if (graph::vertex[a[i]].vis) {
            graph::edge[2 * i].del = false;
            std::cout << 0 << '\n';
        } else {
            graph::edge[2 * i + 1].del = false;
            std::cout << 1 << '\n';
        }
    }
    return 0;
}