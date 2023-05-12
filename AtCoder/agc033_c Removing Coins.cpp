#include <iostream>

const int maxN = 2e5;

int n;
int u, v;
int f[maxN + 10];

namespace graph {
    struct Vertex {
        int head;
        int link;
        int diam;
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

    void DFS(int u, int from) {
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            DFS(v, u);
            vertex[u].diam = std::max(vertex[u].diam, vertex[v].diam);
            vertex[u].diam = std::max(vertex[u].diam, vertex[u].link + vertex[v].link + 1);
            vertex[u].link = std::max(vertex[u].link, vertex[v].link + 1);
        }
        //printf("diam[%d] = %d\n", u, vertex[u].diam);
        //printf("link[%d] = %d\n", u, vertex[u].link);
        return;
    }
}

int main() {
    std::cin >> n;
    for (int i = 1; i < n; i++) {
        std::cin >> u >> v;
        graph::addEdge(u, v);
        graph::addEdge(v, u);
    }
    graph::DFS(1, 0);
    f[0] = true;
    for (int i = 2; i <= n; i++) {
        f[i] = (!f[i - 1]) || (!f[i - 2]);
    }
    if (f[graph::vertex[1].diam]) {
        std::cout << "First" << '\n';
    } else {
        std::cout << "Second" << '\n';
    }
    //std::cout << f[graph::vertex[1].diam] << '\n';
    //printf("%d\n", graph::vertex[1].diam);
    return 0;
}