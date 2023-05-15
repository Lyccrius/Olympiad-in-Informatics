#include <iostream>

const int maxN = 1e5;
const int maxK = 2;

int n, k;
int a, b;
int q, p;
int ans;

namespace graph {
    struct Vertex {
        int head;
        int dep;
        int fa;
        int link;
        int diam;

        Vertex() {
            head = -1;
            return;
        }
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
        int weight;
    } edge[2 * maxN + 10];

    int ecnt;
    
    void addEdge(int tail, int head, int weight) {
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        edge[ecnt].weight = weight;
        vertex[tail].head = ecnt;
        ecnt++;
        return;
    }

    void DFS1(int u, int from) {
        if (vertex[u].dep > vertex[p].dep) p = u;
        for (int e = vertex[u].head; ~e; e = edge[e].next) {
            int v = edge[e].head;
            int w = edge[e].weight;
            if (v == from) continue;
            vertex[v].dep = vertex[u].dep + w;
            vertex[v].fa = u;
            DFS1(v, u);
        }
        return;
    }

    void DFS2(int u) {
        for (int e = vertex[u].head; ~e; e = edge[e].next) {
            int v = edge[e].head;
            if (v != vertex[u].fa) continue;
            edge[e].weight = - edge[e].weight;
            edge[e ^ 1].weight = - edge[e ^ 1].weight;
            DFS2(v);
        }
        return;
    }

    void DFS3(int u, int from) {
        for (int e = vertex[u].head; ~e; e = edge[e].next) {
            int v = edge[e].head;
            int w = edge[e].weight;
            if (v == from) continue;
            DFS3(v, u);
            vertex[u].diam = std::max(vertex[u].diam, vertex[v].diam);
            vertex[u].diam = std::max(vertex[u].diam, vertex[u].link + vertex[v].link + w);
            vertex[u].link = std::max(vertex[u].link, vertex[v].link + w);
        }
        return;
    }
}

int main() {
    std::cin >> n >> k;
    for (int i = 1; i < n; i++) {
        std::cin >> a >> b;
        graph::addEdge(a, b, 1);
        graph::addEdge(b, a, 1);
    }
    ans = 2 * (n - 1);
    p = 1;
    graph::DFS1(p, 0);
    graph::vertex[p].dep = 0;
    graph::vertex[p].fa = 0;
    graph::DFS1(p, 0);
    graph::DFS2(p);
    ans -= graph::vertex[p].dep - 1;
    if (k == 2) {
        graph::DFS3(1, 0);
        ans -= graph::vertex[1].diam - 1;
    }
    std::cout << ans << '\n';
    return 0;
}