#include <iostream>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 500;
const int maxM = 500;
const int maxE = 5e4;

int n, m, e;
int u, v;

namespace graph {
    struct Vertex {
        int match;
        int head;
        int vis;
    } vertex[maxN + maxM + 10];

    struct Edge {
        int head;
        int next;
    } edge[maxE * 2 + 10];

    int ecnt;

    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    void init() {
        for (int u = 1; u <= n + m; u++) {
            vertex[u].vis = false;
        }
        return;
    }

    bool KM(int u) {
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (vertex[v].vis) continue;
            vertex[v].vis = true;
            if (vertex[v].match == 0 || KM(vertex[v].match)) {
                vertex[v].match = u;
                return true;
            }
        }
        return false;
    }
}

int main() {
    promote();
    std::cin >> n >> m >> e;
    for (int i = 1; i <= e; i++) {
        std::cin >> u >> v;
        graph::addEdge(u, v + n);
        graph::addEdge(v + n, u);
    }
    int ans = 0;
    for (int u = 1; u <= n; u++) {
        graph::init();
        if (graph::KM(u)) {
            ans++;
        }
    }
    std::cout << ans;
    return 0;
}