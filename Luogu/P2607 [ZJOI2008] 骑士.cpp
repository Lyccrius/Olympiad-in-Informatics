#include <iostream>

typedef long long lxl;

const int maxN = 1e6;
const int inf = 1e9;

int n;
int w, u;
lxl ans;
lxl f1[maxN + 10][2];
lxl f2[maxN + 10][2];

namespace graph {
    struct Vertex {
        int vis;
        int ins;
        int head;
        int weight;
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
        int del;
    } edge[maxN + 10];

    int ecnt = - 1;

    void init() {
        for (int i = 1; i <= n; i++) vertex[i].head = - 1;
        return;
    }

    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    void DP(int u, int ban, lxl f[][2]) {
        for (int e = vertex[u].head; ~e; e = edge[e].next) {
            int v = edge[e].head;
            if (edge[e].del) continue;
            DP(v, ban, f);
            f[u][0] += std::max(f[v][0], f[v][1]);
        }
        if (u == ban) {
            f[u][1] = - inf;
            return;
        }
        f[u][1] = vertex[u].weight;
        for (int e = vertex[u].head; ~e; e = edge[e].next) {
            int v = edge[e].head;
            if (edge[e].del) continue;
            f[u][1] += f[v][0];
        }
        return;
    }

    void DFS(int u, int from) {
        vertex[u].vis = true;
        vertex[u].ins = true;
        for (int e = vertex[u].head; ~e; e = edge[e].next) {
            int v = edge[e].head;
            if (vertex[v].vis) {
                if (vertex[v].ins) {
                    edge[e].del = true;
                    DP(v, - 1, f1);
                    DP(v, u, f2);
                    ans += std::max(f1[v][0], f2[v][1]);
                }
            } else DFS(v, e);
        }
        vertex[u].ins = false;
        return;
    }
}

int main() {
    std::cin >> n;
    graph::init();
    for (int i = 1; i <= n; i++) {
        std::cin >> w >> u;
        graph::vertex[i].weight = w;
        graph::addEdge(u, i);
    }
    for (int i = 1; i <= n; i++) if (!graph::vertex[i].vis) graph::DFS(i, - 1);
    std::cout << ans;
    return 0;
}