#include <iostream>
#include <algorithm>
#include <deque>

typedef std::deque<int> dic;

const int maxN = 3e5;
const int maxM = 3e5;

int n, m;
int x, y;

namespace graph {
    struct Vertex {
        int head;
        int dfn;
        int low;
        int bel;
        int diam;
        int link;
    };

    struct Edge {
        int tail;
        int head;
        int next;
    };

    Vertex vertex[maxN + 10];
    Edge edge[maxM * 2 + 10];
    int vcnt;
    int ecnt;

    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    void init() {
        vcnt = n;
        ecnt = - 1;
        for (int u = 1; u <= n; u++) vertex[u].head = - 1;
        for (int u = 1; u <= n; u++) vertex[u].bel = u;
        return;
    }

    int dfn;
    dic s;

    std::deque<Edge> cuts;

    namespace tree {
        Vertex vertex[2 * maxN + 10];
        Edge edge[2 * maxN + 10];
        int ecnt;

        void addEdge(int tail, int head) {
            ecnt++;
            edge[ecnt].head = head;
            edge[ecnt].next = vertex[tail].head;
            vertex[tail].head = ecnt;
            return;
        }

        void build() {
            ecnt = - 1;
            for (int u = 1; u <= vcnt; u++) vertex[u].head = - 1;
            for (auto e : cuts) {
                int u = graph::vertex[e.tail].bel;
                int v = graph::vertex[e.head].bel;
                addEdge(u, v);
                addEdge(v, u);
            }
            return;
        }

        void DFS(int u, int from) {
            //printf("DFS %d from %d\n", u, from);
            for (int e = vertex[u].head; ~ e; e = edge[e].next) {
                int v = edge[e].head;
                if (v == from) continue;
                DFS(v, u);
                vertex[u].diam = std::max(vertex[u].diam, vertex[v].diam);
                vertex[u].diam = std::max(vertex[u].diam, vertex[v].link + 1 + vertex[u].link);
                vertex[u].link = std::max(vertex[u].link, vertex[v].link + 1);
            }
            return;
        }
    }

    void addEBCC(int u) {
        vcnt++;
        int v;
        do {
            v = s.back();
            s.pop_back();
            vertex[v].bel = vcnt;
        } while (v != u);
        return;
    }

    void DFS(int u, int from) {
        dfn++;
        vertex[u].dfn = dfn;
        vertex[u].low = dfn;
        s.push_back(u);
        for (int e = vertex[u].head; ~ e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            if (vertex[v].dfn) {
                vertex[u].low = std::min(vertex[u].low, vertex[v].dfn);
            } else {
                DFS(v, u);
                vertex[u].low = std::min(vertex[u].low, vertex[v].low);
                if (vertex[v].low > vertex[u].dfn) {
                    cuts.push_back((Edge) {u, v});
                    //cuts.push_back((Edge) {v, u});
                }
            }
        }
        if (vertex[u].dfn == vertex[u].low) addEBCC(u);
        return;
    }

    void show() {
        for (int i = 1; i <= n; i++) printf("bel[%d] = %d\n", i, vertex[i].bel);
        for (auto e : cuts) printf("%d to %d\n", e.tail, e.head);
        return;
    }
}

int main() {
    std::cin >> n >> m;
    graph::init();
    for (int i = 1; i <= m; i++) {
        std::cin >> x >> y;
        graph::addEdge(x, y);
        graph::addEdge(y, x);
    }
    for (int i = 1; i <= n; i++) if (!graph::vertex[i].dfn) graph::DFS(i, 0);
    //graph::show();
    graph::tree::build();
    graph::tree::DFS(graph::vcnt, 0);
    std::cout << graph::tree::vertex[graph::vcnt].diam;
    return 0;
}