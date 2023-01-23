#include <iostream>
#include <stack>

const int maxN = 1e6;
const int maxM = 1e6;

int n, m;
int i, a, j, b;

namespace graph {
    struct Vertex {
        int head;
        int low;
        int dfn;
        int ins;
        int bel;
    } vertex[maxN * 2 + 10];

    int vcnt;
    int sat[maxN + 10][2];

    void init() {
        for (int i = 1; i <= n; i++) {
            sat[i][0] = ++vcnt;
            sat[i][1] = ++vcnt;
        }
        return;
    }

    struct Edge {
        int head;
        int next;
    } edge[maxM * 2 + 10];

    int ecnt;

    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    int dfn;
    std::stack<int> s;

    int scnt;

    void addSCC(int u) {
        scnt++;
        int v;
        do {
            v = s.top();
            s.pop();
            vertex[v].ins = false;
            vertex[v].bel = scnt;
        } while (v != u);
        return;
    }

    void Tarjan(int u) {
        dfn++;
        vertex[u].low = dfn;
        vertex[u].dfn = dfn;
        vertex[u].ins = true;
        s.push(u);
        for (int e = vertex[u].head; e; e = edge[e].next) {
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
    std::cin >> n >> m;
    graph::init();
    for (int k = 1; k <= m; k++) {
        std::cin >> i >> a >> j >> b;
        graph::addEdge(graph::sat[i][!a], graph::sat[j][b]);
        graph::addEdge(graph::sat[j][!b], graph::sat[i][a]);
    }
    for (int i = 1; i <= n * 2; i++) if (!graph::vertex[i].dfn) graph::Tarjan(i);
    for (int i = 1; i <= n; i++) {
        if (graph::vertex[graph::sat[i][0]].bel == graph::vertex[graph::sat[i][1]].bel) {
            std::cout << "IMPOSSIBLE" << '\n';
            return 0;
        }
    }
    std::cout << "POSSIBLE" << '\n';
    for (int i = 1; i <= n; i++) {
        if (graph::vertex[graph::sat[i][0]].bel < graph::vertex[graph::sat[i][1]].bel) std::cout << 0 << ' ';
        else std::cout << 1 << ' ';
    }
    return 0;
}