#include <iostream>

const int maxN = 1e5;
const int maxM = 1e5;
const int maxC = 1e5;

int n;
int u, v;
int c[maxN + 10];
int m;
int res;
int cnt[maxC + 10];
int ans[maxN + 10];

namespace graph {
    struct Vertex {
        int head;
        int size;
        int hson;
        int dfn;
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

    int dfn;
    int dnf[maxN + 10];

    void DFS0(int u, int from) {
        dfn++;
        vertex[u].dfn = dfn;
        vertex[u].size = 1;
        dnf[dfn] = u;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            DFS0(v, u);
            vertex[u].size += vertex[v].size;
            if (vertex[vertex[u].hson].size < vertex[v].size) vertex[u].hson = v;
        }
        return;
    }

    void add(int u) {
        if (cnt[c[u]] == 0) res++;
        cnt[c[u]]++;
        return;
    }

    void del(int u) {
        cnt[c[u]]--;
        if (cnt[c[u]] == 0) res--;
        return;
    }

    void DFS1(int u, int from, bool keep) {
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            if (v == vertex[u].hson) continue;
            DFS1(v, u, false);
        }
        if (vertex[u].hson) DFS1(vertex[u].hson, u, true);
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            if (v == vertex[u].hson) continue;
            for (int i = vertex[v].dfn; i <= vertex[v].dfn + vertex[v].size - 1; i++) add(dnf[i]);
        }
        add(u);
        ans[u] = res;
        if (!keep) for (int i = vertex[u].dfn; i <= vertex[u].dfn + vertex[u].size - 1; i++) del(dnf[i]);
        return;
    }
}

int main() {
    std::cin >> n;
    for (int i = 1; i < n; i++) std::cin >> u >> v, graph::addEdge(u, v), graph::addEdge(v, u);
    for (int i = 1; i <= n; i++) std::cin >> c[i];
    graph::DFS0(1, 0);
    graph::DFS1(1, 0, true);
    std::cin >> m;
    for (int i = 1; i <= m; i++) std::cin >> u, std::cout << ans[u] << '\n';
    return 0;
}