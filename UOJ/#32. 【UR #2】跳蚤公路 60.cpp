#include <iostream>
#include <deque>
#include <cmath>

typedef long long lxl;
typedef std::deque<int> diq;

const int maxN = 100;
const int maxM = 10000;
const lxl inf = 1e18;

int n, m;
int u, v, w, s;

namespace graph {
    struct Vertex {
        int head;
        int deg;
        int vis;
        lxl d;
        lxl u;

        Vertex() {
            d = - inf;
            u = inf;
            return;
        }
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next; 
    } edge[maxM + 10];

    int ecnt;

    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        vertex[head].deg++;
        return;
    }

    void toposort() {
        diq q;
        for (int u = 1; u <= n; u++) if (!vertex[u].deg) q.push_back(u);
        vertex[1].vis = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop_front();
            for (int e = vertex[u].head; e; e = edge[e].next) {
                int v = edge[e].head;
                vertex[v].deg--;
                if (!vertex[v].deg) q.push_back(v);
                if (vertex[u].vis) {
                    vertex[v].vis = true;
                    vertex[v].d = std::max(vertex[v].d, vertex[u].d);
                    vertex[v].u = std::min(vertex[v].u, vertex[u].u);
                }
            }
        }
        return;
    }
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        std::cin >> u >> v >> w >> s;
        if (u == v) {
            if (s == 1) graph::vertex[u].d = std::max(graph::vertex[u].d, (lxl) ceil(- 1.0 * w / s));
            if (s == -1) graph::vertex[u].u = std::min(graph::vertex[u].u, (lxl) floor(- 1.0 * w / s));
            if (s == 0) if (w < 0) graph::vertex[u].d = inf, graph::vertex[u].u = - inf;
        } else graph::addEdge(u, v);
    }
    graph::toposort();
    for (int i = 1; i <= n; i++) {
        if (graph::vertex[i].d == - inf || graph::vertex[i].u == inf || graph::vertex[i].u - graph::vertex[i].d + 1 > inf) std::cout << -1 << '\n';
        else std::cout << std::max(0ll, graph::vertex[i].u - graph::vertex[i].d + 1) << '\n';
    }
    return 0;
}