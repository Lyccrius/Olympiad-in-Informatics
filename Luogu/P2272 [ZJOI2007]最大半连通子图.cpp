#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>

typedef std::deque<int> diq;

const int maxN = 1e5;
const int maxM = 1e6;
const int maxX = 1e8;

int n, m, x;
int a, b;
int k, c;

namespace graph {
    struct Vertex {
        int head;
        int ins;
        int dfn;
        int low;
        int bel;
        int deg;
        int size;
        int k, c;
    } vertex[maxN + 10];

    struct Edge {
        int tail;
        int head;
        int next;

        bool operator<(const Edge &other) const {
            if (tail != other.tail) return tail < other.tail;
            return head < other.head;
        }

        bool operator==(const Edge &other) const {
            if (tail != other.tail) return false;
            if (head != other.head) return false;
            return true;
        }
    } edge[maxM + 10];

    int ecnt;

    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].tail = tail;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    namespace DAG {
        Vertex vertex[maxN + 10];
        Edge edge[maxM + 10];
        int vcnt;
        int ecnt;
        std::vector<Edge> edges;

        void addEdge(int tail, int head) {
            ecnt++;
            edge[ecnt].tail = tail;
            edge[ecnt].head = head;
            edge[ecnt].next = vertex[tail].head;
            vertex[tail].head = ecnt;
            vertex[head].deg++;
            return;
        }

        void build() {
            for (int e = 1; e <= graph::ecnt; e++) {
                int u = graph::edge[e].tail;
                int v = graph::edge[e].head;
                if (graph::vertex[u].bel == graph::vertex[v].bel) continue;
                edges.push_back((Edge) {graph::vertex[u].bel, graph::vertex[v].bel});
            }
            std::sort(edges.begin(), edges.end());
            edges.erase(std::unique(edges.begin(), edges.end()), edges.end());
            for (auto e : edges) addEdge(e.tail, e.head);
            return;
        }

        void topo() {
            diq q;
            for (int u = 1; u <= vcnt; u++) {
                if (!vertex[u].deg) {
                    vertex[u].c = 1;
                    q.push_back(u);
                }
            }
            while (!q.empty()) {
                int u = q.front();
                q.pop_front();
                vertex[u].k += vertex[u].size;
                if (k < vertex[u].k) {
                    k = vertex[u].k;
                    c = 0;
                }
                if (k == vertex[u].k) {
                    c = (c + vertex[u].c) % x;
                }
                for (int e = vertex[u].head; e; e = edge[e].next) {
                    int v = edge[e].head;
                    if (vertex[v].k < vertex[u].k) {
                        vertex[v].k = vertex[u].k;
                        vertex[v].c = 0;
                    }
                    if (vertex[v].k == vertex[u].k) {
                        vertex[v].c = (vertex[v].c + vertex[u].c) % x;
                    }
                    vertex[v].deg--;
                    if (!vertex[v].deg) q.push_back(v);
                }
            }
            return;
        }
    }

    int dfn;
    diq s;

    void addSCC(int u) {
        ++DAG::vcnt;
        int v;
        do {
            v = s.back();
            s.pop_back();
            vertex[v].bel = DAG::vcnt;
            vertex[v].ins = false;
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
    std::cin >> n >> m >> x;
    for (int i = 1; i <= m; i++) std::cin >> a >> b, graph::addEdge(a, b);
    for (int i = 1; i <= n; i++) if (!graph::vertex[i].dfn) graph::Tarjan(i);
    graph::DAG::build();
    graph::DAG::topo();
    std::cout << k << '\n';
    std::cout << c << '\n';
    return 0;
}