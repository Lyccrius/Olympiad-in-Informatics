#include <iostream>

const int maxN = 14;
const int maxM = 26;

int n, m;
int u, v;
int ans;

namespace graph {
    struct Vertex {
        int head;
        int vis;
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
    } edge[2 * maxM + 10];

    int ecnt;

    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    void DFS(int u, int l) {
        if (!l) {
            ans++;
            return;
        }
        vertex[u].vis = true;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (vertex[v].vis) continue;
            DFS(v, l - 1);
        }
        vertex[u].vis = false;
        return;
    }
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) std::cin >> u >> v, graph::addEdge(u, v), graph::addEdge(v, u);
    for (int l = 1; l <= n - 1; l++) {
        ans = 0;
        graph::DFS(1, l);
        std::cout << ans << '\n';
    }
    return 0;
}