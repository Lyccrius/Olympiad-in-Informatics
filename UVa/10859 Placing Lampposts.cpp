#include <iostream>
#include <algorithm>

const int maxN = 1000;
const int k = 2000;

int T;
int n, m;
int u, v;
int f, g;

namespace graph {
    struct Vertex {
        int head;
        int vis;
        int f[2];
        int g[2];
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
    } edge[maxN * 2 + 10];

    int ecnt;

    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    void init() {
        for (int i = 0; i < n; i++) vertex[i].vis = false;
        for (int i = 0; i < n; i++) vertex[i].head = 0;
        ecnt = 0;
        return;
    }

    void DFS(int u, int from) {
        vertex[u].vis = true;
        vertex[u].f[0] = 0;
        vertex[u].g[0] = 0;
        vertex[u].f[1] = 1;
        vertex[u].g[1] = 0;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            DFS(v, u);
            vertex[u].f[0] += vertex[v].f[1];
            vertex[u].g[0] += vertex[v].g[1];
            if (vertex[v].f[1] < vertex[v].f[0]) {
                vertex[u].f[1] += vertex[v].f[1];
                vertex[u].g[1] += vertex[v].g[1] + 1;
            }  else if (vertex[v].f[1] > vertex[v].f[0]) {
                vertex[u].f[1] += vertex[v].f[0];
                vertex[u].g[1] += vertex[v].g[0];
            } else {
                vertex[u].f[1] += std::max(vertex[v].f[0], vertex[v].f[1]);
                vertex[u].g[1] += std::max(vertex[v].g[0], vertex[v].g[1] + 1);
            }
        }
        /*
        printf("f[%d][%d] = %d\n", u, 0, vertex[u].f[0]);
        printf("g[%d][%d] = %d\n", u, 0, vertex[u].g[0]);
        printf("f[%d][%d] = %d\n", u, 1, vertex[u].f[1]);
        printf("g[%d][%d] = %d\n", u, 1, vertex[u].g[1]);
        */
        return;
    }
}

void mian() {
    std::cin >> n >> m;
    graph::init();
    f = 0;
    g = 0;
    for (int i = 1; i <= m; i++) {
        std::cin >> u >> v;
        graph::addEdge(u, v);
        graph::addEdge(v, u);
    }
    for (int i = 0; i < n; i++) {
        if (!graph::vertex[i].vis) {
            graph::DFS(i, -1);
            if (graph::vertex[i].f[1] < graph::vertex[i].f[0]) {
                f += graph::vertex[i].f[1];
                g += graph::vertex[i].g[1];
            } else if (graph::vertex[i].f[1] > graph::vertex[i].f[0]) {
                f += graph::vertex[i].f[0];
                g += graph::vertex[i].g[0];
            } else {
                f += std::max(graph::vertex[i].f[0], graph::vertex[i].f[1]);
                g += std::max(graph::vertex[i].g[0], graph::vertex[i].g[1]);
            }
        }
    }
    std::cout << f << ' ' << g << ' ' << m - g << '\n';
    return;
}

int main() {
    std::cin >> T;
    while (T--) mian();
    return 0;
}