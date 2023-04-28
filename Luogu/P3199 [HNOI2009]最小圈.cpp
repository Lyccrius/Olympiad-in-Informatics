#include <iostream>
#include <iomanip>

typedef double dbl;

const int maxN = 3000;
const int maxM = 10000;
const int inf = 1e7;
const dbl eps = 1e-9;

int n, m;
int u, v;
dbl w;

namespace graph {
    struct Vertex {
        int head;
        int vis;
        dbl dis;
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
        dbl weight;
    } edge[maxM + 10];

    int ecnt;

    void addEdge(int tail, int head, dbl weight) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        edge[ecnt].weight = weight;
        vertex[tail].head = ecnt;
        return;
    }

    bool DFS(int u, dbl mid) {
        vertex[u].vis = true;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            dbl w = edge[e].weight - mid;
            if (vertex[v].dis > vertex[u].dis + w) {
                vertex[v].dis = vertex[u].dis + w;
                if (vertex[v].vis) return true;
                if (DFS(v, mid)) return true;
            }
        }
        vertex[u].vis = false;
        return false;
    }
}

bool check(dbl mid) {
    for (int i = 1; i <= n; i++) graph::vertex[i].vis = false;
    for (int i = 1; i <= n; i++) graph::vertex[i].dis = 0;
    for (int i = 1; i <= n; i++) if (graph::DFS(i, mid)) return true;
    return false;
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        std::cin >> u >> v >> w;
        graph::addEdge(u, v, w);
    }
    dbl l = -inf;
    dbl r = inf;
    while (r - l > eps) {
        dbl mid = (l + r) / 2;
        if (check(mid)) r = mid;
        else l = mid;
    }
    std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(8) << l << '\n';
    return 0;
}