#include <iostream>

typedef bool bol;

const int maxN = 1e5;

int n;
int a, b;

namespace graph {
    struct Vertex {
        int head;
        int deg;
        int f;
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
    } edge[maxN * 2 + 10];

    int ecnt;
    int root;

    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        vertex[tail].deg++;
        return;
    }

    int isLeaf(int u) {
        return vertex[u].deg == 1;
    }

    bol odd;
    bol even;

    void DFS(int u, int from, int dep) {
        vertex[u].f = 0;
        if (isLeaf(u)) {
            if (dep & 1) {
                odd = true;
            } else {
                even = true;
            }
            return;
        }
        bol toLeaf = false;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            DFS(v, u, dep + 1);
            if (isLeaf(v)) {
                toLeaf = true;
            } else {
                vertex[u].f += vertex[v].f + 1;
            }
        }
        if (toLeaf) vertex[u].f++;
        return;
    }

    int low;
    int high;

    void mian() {
        for (int i = 1; i <= n; i++) if (vertex[i].deg > 1) root = i;
        DFS(root, 0, 0);
        low = (odd ^ even) ? 1 : 3;
        //std::cout << odd << ' ' << even;
        high = vertex[root].f;
        std::cout << low << ' ' << high;
        //for (int i = 1; i <= n; i++) printf("%d ", vertex[i].f);
        return;
    }
}

int main() {
    std::cin >> n;
    for (int i = 1; i < n; i++) {
        std::cin >> a >> b;
        graph::addEdge(a, b);
        graph::addEdge(b, a);
    }
    graph::mian();
    return 0;
}