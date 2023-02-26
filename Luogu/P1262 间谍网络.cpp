#include <iostream>
#include <algorithm>
#include <stack>

const int maxN = 3000;
const int maxR = 8000;
const int maxP = 20000;

int n;
int p;
int X, Y;
int r;
int A, B;
int ans;

namespace graph {
    struct Vertex {
        int head;
        int ready;
        int price;
        int degree;
        int dfn;
        int low;
        int ins;
        int bel;
    };

    struct Edge {
        int head;
        int next;
    };

    Vertex vertex[maxN + 10];
    Edge edge[maxR + 10];

    int ecnt;

    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    namespace DAG {
        Vertex vertex[maxN + 10];
        Edge edge[maxR + 10];

        int vcnt;
        int ecnt;

        void addEdge(int tail, int head) {
            ecnt++;
            edge[ecnt].head = head;
            edge[ecnt].next = vertex[tail].head;
            vertex[tail].head = ecnt;
            return;
        }
    }

    int dfn;
    std::stack<int> s;

    void addSCC(int u) {
        DAG::vcnt++;
        DAG::vertex[DAG::vcnt].price = maxP + 10;
        int v;
        do {
            v = s.top();
            s.pop();
            vertex[v].ins = false;
            vertex[v].bel = DAG::vcnt;
            if (!vertex[v].ready) continue;
            DAG::vertex[DAG::vcnt].price = std::min(DAG::vertex[DAG::vcnt].price, vertex[v].price);
        } while (v != u);
        return;
    }

    void Tarjan(int u) {
        dfn++;
        vertex[u].dfn = dfn;
        vertex[u].low = dfn;
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
        if (vertex[u].dfn == vertex[u].low) addSCC(u);
        return;
    }

    void mian() {
        for (int u = 1; u <= n; u++) if (!vertex[u].dfn && vertex[u].ready) Tarjan(u);
        for (int u = 1; u <= n; u++) if (!vertex[u].dfn) {
            std::cout << "NO" << '\n';
            std::cout << u << '\n';
            return;
        }
        for (int u = 1; u <= n; u++) {
            for (int e = vertex[u].head; e; e = edge[e].next) {
                int v = edge[e].head;
                if (vertex[u].bel == vertex[v].bel) continue;
                DAG::vertex[vertex[v].bel].degree++;
            }
        }
        for (int u = 1; u <= DAG::vcnt; u++) if (!DAG::vertex[u].degree) ans += DAG::vertex[u].price;
        std::cout << "YES" << '\n';
        std::cout << ans << '\n';
        return;
    }
}

int main() {
    std::cin >> n;
    std::cin >> p;
    for (int i = 1; i <= p; i++) std::cin >> X >> Y, graph::vertex[X].ready = true, graph::vertex[X].price = Y;
    std::cin >> r;
    for (int i = 1; i <= r; i++) std::cin >> A >> B, graph::addEdge(A, B);
    graph::mian();
    return 0;
}