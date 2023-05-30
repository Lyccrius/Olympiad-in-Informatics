#include <iostream>

typedef long long lxl;

const int maxN = 50000;
const int maxM = 100000;
const int logN = 16;
const int logD = 60;

int n, m;
lxl s, t, d;

struct LinearBasis {
    lxl b[logD + 5];

    void insert(lxl x) {
        for (int p = logD; p >= 0; p--) {
            if ((x & (1ll << p)) == 0) continue;
            if (b[p] == 0) {
                b[p] = x;
                return;
            }
            x ^= b[p];
        }
        return;
    }

    lxl query(lxl x) {
        for (int p = logD; p >= 0; p--) x = std::max(x, x ^ b[p]);
        return x;
    }

    LinearBasis operator+(const LinearBasis &other) const {
        LinearBasis ret = *this;
        for (int p = logD; p >= 0; p--) if (other.b[p]) ret.insert(other.b[p]);
        return ret;
    }
} lab;

namespace graph {
    struct Vertex {
        int head;
        int vis;
        lxl dis;
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
        lxl weight;
    } edge[2 * maxM + 10];

    int ecnt;

    void addEdge(int tail, int head, lxl weight) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        edge[ecnt].weight = weight;
        vertex[tail].head = ecnt;
        return;
    }

    void DFS(int u) {
        vertex[u].vis = true;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            lxl w = edge[e].weight;
            if (vertex[v].vis == false) {
                vertex[v].dis = vertex[u].dis ^ w;
                DFS(v);
            } else {
                lab.insert(vertex[u].dis ^ vertex[v].dis ^ w);
            }
        }
        return;
    }
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) std::cin >> s >> t >> d, graph::addEdge(s, t, d), graph::addEdge(t, s, d);
    graph::DFS(1);
    std::cout << lab.query(graph::vertex[n].dis) << '\n';
    return 0;
}