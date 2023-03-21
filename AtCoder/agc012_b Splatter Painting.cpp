#include <iostream>
#include <algorithm>

const int maxN = 1e5;
const int maxM = 1e5;
const int maxQ = 1e5;
const int maxC = 1e5;

int N, M;
int a[maxM + 10], b[maxM + 10];
int Q;
int v[maxQ + 10], d[maxQ + 10], c[maxQ + 10];

namespace graph {
    struct Vertex {
        int head;
        int dis;
        int col;
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
    } edge[maxM * 2 + 10];

    int ecnt;

    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    void DFS(int u, int d, int c) {
        if (vertex[u].col == 0) vertex[u].col = c;
        if (vertex[u].dis >= d) return;
        if (d == 0) return;
        vertex[u].dis = d;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            DFS(v, d - 1, c);
        }
        return;
    }
}

int main() {
    std::cin >> N >> M;
    for (int i = 1; i <= M; i++) {
        std::cin >> a[i] >> b[i];
        graph::addEdge(a[i], b[i]);
        graph::addEdge(b[i], a[i]);
    }
    std::cin >> Q;
    for (int i = 1; i <= Q; i++) std::cin >> v[i] >> d[i] >> c[i];
    for (int i = Q; i >= 1; i--) graph::DFS(v[i], d[i], c[i]);
    for (int i = 1; i <= N; i++) std::cout << graph::vertex[i].col << '\n';
    return 0;
}