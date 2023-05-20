#include <iostream>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 1e6;

int n;
int u, v;

namespace graph {
    struct Vertex {
        int head;
        int hson;
        int size;
        int dfn;
        int dep;
        int ans;
    } vertex[maxN];

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
        vertex[u].size = 1;
        vertex[u].dfn = ++dfn;
        vertex[u].dep = vertex[from].dep + 1;
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

    int cnt[maxN + 10];
    int res;

    void add(int u) {
        cnt[vertex[u].dep]++;
        if (cnt[vertex[u].dep] > cnt[res]) res = vertex[u].dep;
        if (cnt[vertex[u].dep] == cnt[res] && vertex[u].dep < res) res = vertex[u].dep;
        return;
    }

    void del(int u) {
        cnt[vertex[u].dep]--;
        return;
    }

    void DFS1(int u, int from, int flag) {
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            if (v == vertex[u].hson) continue;
            DFS1(v, u, 0);
        }
        if (vertex[u].hson) DFS1(vertex[u].hson, u, 1);
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            if (v == vertex[u].hson) continue;
            for (int i = vertex[v].dfn; i <= vertex[v].dfn + vertex[v].size - 1; i++) add(dnf[i]);
        }
        add(u);
        if (cnt[res] == 0) res = vertex[u].dep;
        vertex[u].ans = res - vertex[u].dep; 
        if (!flag) for (int i = vertex[u].dfn; i <= vertex[u].dfn + vertex[u].size - 1; i++) del(dnf[i]);
    }
}

int main() {
    promote();
    std::cin >> n;
    for (int i = 1; i <= n - 1; i++) std::cin >> u >> v, graph::addEdge(u, v), graph::addEdge(v, u);
    graph::DFS0(1, 0);
    graph::DFS1(1, 0, 1);
    for (int i = 1; i <= n; i++) std::cout << graph::vertex[i].ans << '\n';
    return 0;
}