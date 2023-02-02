#include <iostream>
#include <algorithm>

const int maxN = 3e5;

int n, s;
int u, v, w;
int p;
int q;
int d;

namespace graph {
    struct Vertex {
        int head;
        int dis;
        int ond;
        int fa;
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
        int weight;
    } edge[maxN * 2 + 10];

    int ecnt;

    void addEdge(int tail, int head, int weight) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].weight = weight;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    void DFS(int u, int from) {
        //printf("DFS %d from %d, %d\n", u, from, vertex[u].dis);
        vertex[u].fa = from;
        d = std::max(d, vertex[u].dis);
        if (vertex[p].dis < vertex[u].dis) p = u;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            int w = edge[e].weight;
            if (v == from) continue;
            if (vertex[v].ond) continue;
            vertex[v].dis = vertex[u].dis + w;
            vertex[v].ond |= vertex[u].ond;
            DFS(v, u);
        }
        return;
    }

    void mian() {
        int ans = d;
        for (int u = p, v = p; u; u = vertex[u].fa) {
            while (vertex[v].dis - vertex[u].dis > s) v = vertex[v].fa;
            ans = std::min(ans, std::max(vertex[u].dis, vertex[p].dis - vertex[v].dis));
        }
        d = 0;
        for (int u = p; u; u = vertex[u].fa) vertex[u].ond = true;
        for (int u = p; u; u = vertex[u].fa) vertex[u].dis = 0, DFS(u, vertex[u].fa);
        ans = std::max(ans, d);
        std::cout << ans;
        return;
    }
}

int main() {
    std::cin >> n >> s;
    for (int i = 1; i < n; i++) std::cin >> u >> v >> w, graph::addEdge(u, v, w), graph::addEdge(v, u, w);
    p = 1;
    graph::vertex[p].dis = 0;
    graph::DFS(p, 0);
    q = p;
    graph::vertex[p].dis = 0;
    graph::DFS(p, 0);
    //printf("diameter: %d to %d\n", p, q);
    graph::mian();
    return 0;
}