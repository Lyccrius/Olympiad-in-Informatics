#include <iostream>

typedef long long lxl;

const int maxN = 2e4;
const int maxQ = 2e5;
const int logN = 15;
const int logG = 60;

int n, q;
lxl g[maxN + 10];
int x, y;

typedef struct LinearBasis {
    lxl b[logG + 5];

    LinearBasis() {
        std::fill(b, b + sizeof(b) / 8, 0);
        return;
    }

    void insert(lxl x) {
        for (int p = logG; p >= 0; p--) {
            if ((x & (1ll << p)) == 0) continue;
            if (b[p] == 0) {
                b[p] = x;
                return;
            }
            x ^= b[p];
        }
        return;
    }

    LinearBasis operator+(const LinearBasis &other) const {
        LinearBasis ret = *this;
        for (int p = logG; p >= 0; p--) if (other.b[p]) ret.insert(other.b[p]);
        return ret;
    }
} lab;

namespace graph {
    struct Vertex {
        int head;
        int next;
        int dep;
        int f[logN + 5];
        lab b[logN + 5];
    } vertex[maxN + 10];
    
    struct Edge {
        int head;
        int next;
    } edge[2 * maxN + 10];

    int ecnt;

    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    void DFS(int u, int from) {
        vertex[u].dep = vertex[from].dep + 1;
        vertex[u].f[0] = from;
        vertex[u].b[0].insert(g[u]);
        for (int p = 1; p <= logN; p++) {
            vertex[u].f[p] = vertex[vertex[u].f[p - 1]].f[p - 1];
            vertex[u].b[p] = vertex[vertex[u].f[p - 1]].b[p - 1] + vertex[u].b[p - 1];
        }
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            DFS(v, u);
        }
        return;
    }

    lxl query(int u, int v) {
        lxl ret = 0;
        lab res;
        if (vertex[u].dep < vertex[v].dep) std::swap(u, v);
        for (int p = logN; p >= 0; p--) {
            if (vertex[vertex[u].f[p]].dep >= vertex[v].dep) {
                res = res + vertex[u].b[p];
                u = vertex[u].f[p];
            }
        }
        if (u == v) {
            res.insert(g[u]);
        } else {
            for (int p = logN; p >= 0; p--) {
                if (vertex[u].f[p] != vertex[v].f[p]) {
                    res = res + vertex[u].b[p];
                    res = res + vertex[v].b[p];
                    u = vertex[u].f[p];
                    v = vertex[v].f[p];
                }
            }
            res.insert(g[u]);
            res.insert(g[v]);
            res.insert(g[vertex[u].f[0]]);
        }
        for (int p = logG; p >= 0; p--) ret = std::max(ret, ret ^ res.b[p]);
        return ret;
    }
}

int main() {
    std::cin >> n >> q;
    for (int i = 1; i <= n; i++) std::cin >> g[i];
    for (int i = 1; i <= n - 1; i++) std::cin >> x >> y, graph::addEdge(x, y), graph::addEdge(y, x);
    graph::DFS(1, 0);
    for (int i = 1; i <= q; i++) std::cin >> x >> y, std::cout << graph::query(x, y) << '\n';
    return 0;
}