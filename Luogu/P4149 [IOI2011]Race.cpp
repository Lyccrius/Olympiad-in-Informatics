#include <iostream>
#include <map>

typedef long long lxl;
typedef std::map<lxl, int> mli;

const int maxN = 2e5;
const int maxK = 1e6;
const int maxW = 1e6;

int n, k;
int u, v, w;
int ans = maxN + 10;

namespace graph {
    struct Vertex {
        int head;
        int size;
        int hson;
        lxl dis;
        int dep;
        int dfn;
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
        int weight;
    } edge[2 * maxN + 10];

    int ecnt;
    int dfn;
    int dnf[maxN + 10];

    void addEdge(int tail, int head, int weight) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        edge[ecnt].weight = weight;
        vertex[tail].head = ecnt;
        return;
    }

    void AddEdge(int tail, int head, int weight) {
        addEdge(tail, head, weight);
        addEdge(head, tail, weight);
        return;
    }

    void DFS1(int u, int from) {
        dfn++;
        vertex[u].dfn = dfn;
        vertex[u].size = 1;
        dnf[dfn] = u;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            int w = edge[e].weight;
            if (v == from) continue;
            vertex[v].dep = vertex[u].dep + 1;
            vertex[v].dis = vertex[u].dis + w;
            DFS1(v, u);
            vertex[u].size += vertex[v].size;
            if (vertex[v].size > vertex[vertex[u].hson].size) vertex[u].hson = v;
        }
        return;
    }

    mli res;

    void add(int u) {
        if (res[vertex[u].dis] == 0) res[vertex[u].dis] = maxN + 10;
        res[vertex[u].dis] = std::min(res[vertex[u].dis], vertex[u].dep);
        return;
    }

    void del(int u) {
        res[vertex[u].dis] = 0;
        return;
    }

    void DFS2(int u, int from, int keep) {
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            if (v == vertex[u].hson) continue;
            DFS2(v, u, false);
        }
        if (vertex[u].hson) DFS2(vertex[u].hson, u, true);
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            if (v == vertex[u].hson) continue;
            for (int i = vertex[v].dfn; i <= vertex[v].dfn + vertex[v].size - 1; i++) {
                lxl req = k - (vertex[dnf[i]].dis - vertex[u].dis) + vertex[u].dis;
                if (res[req]) ans = std::min(ans, res[req] + (vertex[dnf[i]].dep - vertex[u].dep) - vertex[u].dep);
            }
            for (int i = vertex[v].dfn; i <= vertex[v].dfn + vertex[v].size - 1; i++) add(dnf[i]);
        }
        add(u);
        if (res[vertex[u].dis + k]) ans = std::min(ans, res[vertex[u].dis + k] - vertex[u].dep);
        if (!keep) for (int i = vertex[u].dfn; i <= vertex[u].dfn + vertex[u].size - 1; i++) del(dnf[i]);
        return;
    }
}

int main() {
    std::cin >> n >> k;
    for (int i = 1; i <= n - 1; i++) std::cin >> u >> v >> w, graph::AddEdge(u + 1, v + 1, w);
    graph::DFS1(1, 0);
    graph::DFS2(1, 0, true);
    if (ans > maxN) ans = -1;
    std::cout << ans << '\n';
    return 0;
}