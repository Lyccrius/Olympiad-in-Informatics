#include <iostream>
#include <deque>

typedef std::deque<int> dic;

const int maxN = 1e4;
const int maxM = 5e4;

int N, M;
int A, B;
int ans;

namespace graph {
    struct Vertex {
        int head;
        int dfn;
        int low;
        int ins;
        int bel;
        int deg;
        int size;
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
        return;
    }

    int dfn;
    dic s;

    namespace DAG {
        Vertex vertex[maxN + 10];
        Edge edge[maxM + 10];
        int vcnt;
        int ecnt;

        void addEdge(int tail, int head) {
            ecnt++;
            edge[ecnt].head = head;
            edge[ecnt].next = vertex[tail].head;
            vertex[tail].head = ecnt;
            vertex[tail].deg++;
            return;
        }

        void build() {
            for (int u = 1; u <= N; u++) {
                for (int e = graph::vertex[u].head; e; e = graph::edge[e].next) {
                    int v = graph::edge[e].head;
                    if (graph::vertex[u].bel == graph::vertex[v].bel) continue;
                    addEdge(graph::vertex[u].bel, graph::vertex[v].bel);
                }
            }
            return;
        }

        void mian() {
            int zero = 0;
            for (int u = 1; u <= vcnt; u++) {
                if (vertex[u].deg == 0) {
                    if (zero) {
                        std::cout << 0 << '\n';
                        return;
                    }
                    zero = u;
                }
            }
            std::cout << vertex[zero].size << '\n';
            return;
        }
    }

    void addSCC(int u) {
        int v;
        DAG::vcnt++;
        do {
            v = s.back();
            s.pop_back();
            vertex[v].bel = DAG::vcnt;
            DAG::vertex[DAG::vcnt].size++;
        } while (v != u);
        return;
    }

    void Tarjan(int u) {
        dfn++;
        vertex[u].dfn = dfn;
        vertex[u].low = dfn;
        vertex[u].ins = true;
        s.push_back(u);
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (vertex[v].dfn) {
                if (vertex[v].ins == false) continue;
                vertex[u].low = std::min(vertex[u].low, vertex[v].dfn);
            } else {
                Tarjan(v);
                vertex[u].low = std::min(vertex[u].low, vertex[v].low);
            }
        }
        if (vertex[u].dfn == vertex[u].low) addSCC(u);
        return;
    }
}

int main() {
    std::cin >> N >> M;
    for (int i = 1; i <= M; i++) {
        std::cin >> A >> B;
        graph::addEdge(A, B);
    }
    for (int i = 1; i <= N; i++) {
        if (!graph::vertex[i].dfn) {
            graph::Tarjan(i);
        }
    }
    graph::DAG::build();
    graph::DAG::mian();
    return 0;
}