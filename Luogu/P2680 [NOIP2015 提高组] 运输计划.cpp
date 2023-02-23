#include <iostream>
#include <algorithm>

const int maxN = 3e5;
const int maxM = 3e5;
const int logN = 19;

int n, m;
int a[maxN + 10], b[maxN + 10], t[maxN + 10];
int u[maxM + 10], v[maxM + 10];
int g[maxM + 10], l[maxM + 10];
int sumL;
int maxL;

namespace graph {
    struct Vertex {
        int head;
        int dep;
        int dis;
        int dif;
        int pre;
        int val;
    } vertex[maxN + 10];
    
    struct Edge {
        int head;
        int next;
        int weight;
    } edge[maxM * 2 + 10];

    int ecnt;

    void addEdge(int tail, int head, int weight) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        edge[ecnt].weight = weight;
        vertex[tail].head = ecnt;
        return;
    }

    struct SparseTable {
        struct Node {
            int f;
        } node[maxN + 10][logN + 5];
    } ST;

    void DFS4Sparse(int u, int from) {
        for (int p = 1; p <= logN; p++) {
            ST.node[u][p].f = ST.node[ST.node[u][p - 1].f][p - 1].f;
        }
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            int w = edge[e].weight;
            if (v == from) continue;
            ST.node[v][0].f = u;
            vertex[v].dep = vertex[u].dep + 1;
            vertex[v].dis = vertex[u].dis + w;
            vertex[v].val = w;
            DFS4Sparse(v, u);
        }
        return;
    }

    int LCA(int u, int v) {
        if (vertex[u].dep < vertex[v].dep) std::swap(u, v);
        for (int p = logN; p >= 0; p--) {
            if (vertex[ST.node[u][p].f].dep >= vertex[v].dep) {
                u = ST.node[u][p].f;
            }
        }
        if (u == v) return u;
        for (int p = logN; p >= 0; p--) {
            if (ST.node[u][p].f != ST.node[v][p].f) {
                u = ST.node[u][p].f;
                v = ST.node[v][p].f;
            }
        }
        return ST.node[u][0].f;
    }

    int tot;
    int cut;

    void init() {
        for (int u = 1; u <= n; u++) vertex[u].dif = 0;
        for (int u = 1; u <= n; u++) vertex[u].pre = 0;
        tot = 0;
        cut = 0;
        return;
    }

    void DFS4Check(int u, int from) {
        vertex[u].pre = vertex[u].dif;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            DFS4Check(v, u);
            vertex[u].pre += vertex[v].pre;
        }
        if (cut < vertex[u].val && vertex[u].pre == tot) {
            cut = vertex[u].val;
        }
        return;
    }

    bool check(int x) {
        init();
        for (int j = 1; j <= m; j++) {
            if (l[j] > x) {
                vertex[u[j]].dif++;
                vertex[v[j]].dif++;
                vertex[g[j]].dif--;
                vertex[g[j]].dif--;
                tot++;
            }
        }
        DFS4Check(1, 0);
        return maxL - cut <= x;
    }

    void mian() {
        DFS4Sparse(1, 0);
        for (int j = 1; j <= m; j++) g[j] = LCA(u[j], v[j]);
        for (int j = 1; j <= m; j++) l[j] = vertex[u[j]].dis + vertex[v[j]].dis - vertex[g[j]].dis * 2;
        for (int j = 1; j <= m; j++) maxL = std::max(maxL, l[j]);
        int l = 0;
        int r = maxL;
        while (l < r) {
            int mid = (l + r) / 2;
            if (check(mid)) r = mid;
            else l = mid + 1;
        }
        std::cout << l;
        return;
    }
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i < n; i++) std::cin >> a[i] >> b[i] >> t[i], graph::addEdge(a[i], b[i], t[i]), graph::addEdge(b[i], a[i], t[i]);
    for (int j = 1; j <= m; j++) std::cin >> u[j] >> v[j];
    graph::mian();
    return 0;
}