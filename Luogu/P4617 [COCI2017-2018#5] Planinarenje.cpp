#include <iostream>

const int maxN = 5000;
const int maxM = 5000;

int n, m;
int u, v;

namespace graph {
    struct Vertex {
        int vis;
        int head;
        int match;
        int must;

        Vertex() {
            must = true;
            return;
        }
    } vertex[2 * maxN + 10];

    struct Edge {
        int head;
        int next;
    }   edge[maxM + 10];

    int ecnt;

    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    bool DFS1(int u, int t) {
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (vertex[v].vis == t) continue;
            vertex[v].vis = t;
            if (vertex[v].match == 0 || DFS1(vertex[v].match, t)) {
                vertex[v].match = u;
                return true;
            }
        }
        return false;
    }

    void DFS2(int u, int t) {
        vertex[u].must = false;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (vertex[v].vis == t) continue;
            vertex[v].vis = t;
            if (vertex[v].match) DFS2(vertex[v].match, t);
        }
        return;
    }
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) std::cin >> u >> v, graph::addEdge(u, n + v);
    for (int i = 1; i <= n; i++) if (!graph::DFS1(i, i)) graph::DFS2(i, i + n);
    for (int i = 1; i <= n; i++) if (graph::vertex[i].must) std::cout << "Slavko" << '\n'; else std::cout << "Mirko" << '\n';
    return 0;
}