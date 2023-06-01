#include <iostream>

typedef char chr;
typedef bool bol;

const int maxN = 2e5;

int t;
int n;
int a, b;
chr s[maxN + 10];
bol flag;

namespace graph {
    struct Vertex {
        int head;
        int size;
        int s;
        int t;
    } vertex[maxN + 10], e;

    struct Edge {
        int head;
        int next;
    } edge[2 * maxN + 10];

    int ecnt;

    void clear() {
        for (int i = 1; i <= n; i++) vertex[i] = e;
        ecnt = 0;
        return;
    }

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
            vertex[u].size++;
            if (v == from) continue;
            DFS(v, u);
            if (!vertex[v].s) vertex[v].s = vertex[u].t;
        }
        int need = (vertex[u].size + 1) / 2;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            need -= vertex[v].s == vertex[u].t;
        }
        if (need > 0 && from && !vertex[from].s) vertex[from].s = vertex[u].t, need--;
        if (need > 0 ) flag = false;
        return; 
    }
}

void mian() {
    graph::clear();
    flag = true;
    std::cin >> n;
    for (int i = 1; i <= n - 1; i++) std::cin >> a >> b, graph::addEdge(a, b), graph::addEdge(b, a);
    std::cin >> (s + 1);
    for (int i = 1; i <= n; i++) {
        if (s[i] == 'B') graph::vertex[i].t = 1;
        if (s[i] == 'W') graph::vertex[i].t = 2;
    }
    graph::DFS(1, 0);
    if (!flag) {
        std::cout << -1 << '\n';
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (graph::vertex[i].s == 1) std::cout << 'B';
        else std::cout << 'W';
    }
    std::cout << '\n';
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}