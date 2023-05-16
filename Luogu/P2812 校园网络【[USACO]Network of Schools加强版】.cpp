#include <iostream>
#include <deque>

typedef std::deque<int> diq;

const int maxN = 10000;
const int maxM = 50000;

int n;
int a, b;

namespace graph {
    struct Vertex {
        int head;
        int dfn;
        int low;
        int bel;
        int ins;
        int ideg;
        int odeg;

        Vertex() {
            head = -1;
        }
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
    } edge[maxM + 10];

    int ecnt;

    void addEdge(int tail, int head) {
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        ecnt++;
        return;
    }

    namespace DAG {
        Vertex vertex[maxN + 10];
        Edge edge[maxM + 10];
        int vcnt;
        int ecnt;

        void addEdge(int tail, int head) {
            edge[ecnt].head = head;
            edge[ecnt].next = vertex[tail].head;
            vertex[tail].head = ecnt;
            vertex[tail].odeg++;
            vertex[head].ideg++;
            ecnt++;
            return;
        }

        void build() {
            for (int u = 1; u <= n; u++) {
                for (int e = graph::vertex[u].head; ~e; e = graph::edge[e].next) {
                    int v = graph::edge[e].head;
                    if (graph::vertex[u].bel == graph::vertex[v].bel) continue;
                    addEdge(graph::vertex[u].bel, graph::vertex[v].bel);
                }
            }
            return;
        }

        void solve() {
            for (int u = 1; u <= vcnt; u++) if (!vertex[u].ideg) a++;
            for (int u = 1; u <= vcnt; u++) if (!vertex[u].odeg) b++;
            return;
        }
    }

    int dfn;
    diq s;

    void addSCC(int u) {
        DAG::vcnt++;
        int v;
        do {
            v = s.back();
            s.pop_back();
            vertex[v].ins = false;
            vertex[v].bel = DAG::vcnt;
        } while (v != u);
        return;
    }

    void Tarjan(int u) {
        dfn++;
        vertex[u].dfn = dfn;
        vertex[u].low = dfn;
        vertex[u].ins = true;
        s.push_back(u);
        for (int e = vertex[u].head; ~e; e = edge[e].next) {
            int v = edge[e].head;
            if (!vertex[v].dfn) {
                Tarjan(v);
                vertex[u].low = std::min(vertex[u].low, vertex[v].low);
            } else if (vertex[v].ins) {
                vertex[u].low = std::min(vertex[u].low, vertex[v].dfn);
            }
        }
        if (vertex[u].low == vertex[u].dfn) addSCC(u);
        return;
    }
}

int main() {
    std::cin >> n;
    for (int i = 1, j = 1; i <= n; i++)  while (std::cin >> j && j) graph::addEdge(i, j);
    for (int i = 1; i <= n; i++) if (!graph::vertex[i].dfn) graph::Tarjan(i);
    graph::DAG::build();
    graph::DAG::solve();
    if (graph::DAG::vcnt == 1) {
        std::cout << 1 << '\n';
        std::cout << 0 << '\n';
        return 0;
    }
    std::cout << a << '\n';
    std::cout << std::max(a, b) << '\n';
    return 0;
}