#include <iostream>
#include <algorithm>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 1e5;
const int maxM = 5e5;
const int inf = 1e9;

int n, m;
int p[maxN + 10];
int x, y, z;

namespace graph {
    struct Vertex {
        int head;
        int minP;
        int f;
    };

    struct Edge {
        int head;
        int next;
    };

    Vertex vertex[maxN + 10];
    Edge edge[maxM * 2 + 10];
    int ecnt;

    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    void DFS(int u, int from, int minP) {
        bool edited = false;
        minP = std::min(minP, p[u]);
        if (vertex[u].minP > minP) {
            vertex[u].minP = minP;
            edited = true;
        }
        int maxF = std::max(vertex[from].f, p[u] - minP);
        if (vertex[u].f < maxF) {
            vertex[u].f = maxF;
            edited = true;
        }
        if (edited == false) return;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            DFS(v, u, minP);
        }
    }
}

int main() {
    promote();
    std::cin >> n >> m;
    for (int i = 0; i <= n; i++) graph::vertex[i].minP = inf;
    for (int i = 1; i <= n; i++) std::cin >> p[i];
    for (int i = 1; i <= m; i++) {
        std::cin >> x >> y >> z;
        if (z == 1) {
            graph::addEdge(x, y);
        }else{
            graph::addEdge(x, y);
            graph::addEdge(y, x);
        }
    }
    graph::DFS(1, 0, inf);
    std::cout << graph::vertex[n].f;
    return 0;
}