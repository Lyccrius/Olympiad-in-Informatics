#include <iostream>
#include <deque>

typedef std::deque<int> dic;

const int maxN = 5e5;
const int maxM = 2e6;

int n, m;
int u, v;

namespace graph {
    struct Vertex {
        int head;
        int dfn;
        int low;
    } vertex[maxN + 10];

    void init() {
        for (int i = 1; i <= n; i++) {
            vertex[i].head = - 1;
        }
        return;
    }

    struct Edge {
        int head;
        int next;
    } edge[maxM * 2 + 10];

    int ecnt = 1;

    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    int dfn;
    dic s;

    struct ebcc {
        dic V;
    } ebcc[maxN + 10];

    int ccnt;

    void addEbcc(int u) {
        ccnt++;
        int v;
        do {
            v = s.back();
            s.pop_back();
            ebcc[ccnt].V.push_back(v);
        } while (v != u);
        return;
    }

    void DFS(int u, int from) {
        ++dfn;
        vertex[u].dfn = dfn;
        vertex[u].low = dfn;
        s.push_back(u);
        for (int e = vertex[u].head; ~ e; e = edge[e].next) {
            int v = edge[e].head;
            if (e == (from ^ 1)) continue;
            if (vertex[v].dfn) {
                vertex[u].low = std::min(vertex[u].low, vertex[v].dfn);
            } else {
                DFS(v, e);
                vertex[u].low = std::min(vertex[u].low, vertex[v].low);
            }
        }
        if (vertex[u].dfn == vertex[u].low) {
            addEbcc(u);
        }
        return;
    }
}

int main() {
    std::cin >> n >> m; graph::init();
    for (int i = 1; i <= m; i++) {
        std::cin >> u >> v;
        if (u == v) continue;
        graph::addEdge(u, v);
        graph::addEdge(v, u);
    }
    for (int i = 1; i <= n; i++) {
        if (!graph::vertex[i].dfn) {
            graph::DFS(i, - 1);
        }
    }
    std::cout << graph::ccnt << '\n';
    for (int i = 1; i <= graph::ccnt; i++) {
        std::cout << graph::ebcc[i].V.size() << ' ';
        for (auto u : graph::ebcc[i].V) std::cout << u << ' ';
        std::cout << '\n';
    }
    return 0;
}