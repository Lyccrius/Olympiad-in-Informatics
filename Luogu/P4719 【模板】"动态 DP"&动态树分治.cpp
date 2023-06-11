#include <iostream>

const int maxN = 1e5;
const int maxM = 1e5;
const int inf = 1e9 + 10;

int n, m;
int a[maxN + 10];
int u, v;
int x, y;
int dnf[maxN + 10];

struct Matrix {
    int n, m;
    int a[5][5];

    Matrix() {
        n = 2;
        m = 2;
        std::fill(a[0], a[0] + sizeof(a) / 4, 0);
        return;
    }

    Matrix operator*(Matrix other) const {
        Matrix ret;
        for (int i = 1; i <= ret.n; i++) {
            for (int j = 1; j <= ret.m; j++) {
                for (int k = 1; k <= m; k++) {
                    ret.a[i][j] = std::max(ret.a[i][j], a[i][k] + other.a[k][j]);
                }
            }
        }
        return ret;
    }
} g[maxN + 10];

struct SegmentTree {
    struct Node {
        Matrix a;
    } node[4 * maxN + 10];

    void PushUp(int u) {
        node[u].a = node[2 * u].a * node[2 * u + 1].a;
        return;
    }

    void Build(int u, int l, int r) {
        if (l == r) {
            node[u].a = g[dnf[l]];
            return;
        }
        int mid = (l + r) / 2;
        Build(2 * u, l, mid);
        Build(2 * u + 1, mid + 1, r);
        PushUp(u);
        return;
    }

    void Modify(int u, int l, int r, int pos) {
        if (l == r) {
            node[u].a = g[dnf[pos]];
            return;
        }
        int mid = (l + r) / 2;
        if (pos <= mid) Modify(2 * u, l, mid, pos);
        if (pos >= mid + 1) Modify(2 * u + 1, mid + 1, r, pos);
        PushUp(u);
        return;
    }

    Matrix Query(int u, int l, int r, int s, int t) {
        if (s <= l && r <= t) return node[u].a;
        int mid = (l + r) / 2;
        if (t <= mid) return Query(2 * u, l, mid, s, t);
        if (s >= mid + 1) return Query(2 * u + 1, mid + 1, r, s, t);
        return Query(2 * u, l, mid, s, t) * Query(2 * u + 1, mid + 1, r, s, t);
    }
} SGT;

namespace graph {
    struct Vertex {
        int head;
        int hson;
        int size;
        int dep;
        int dfn;
        int top;
        int end;
        int fa;
        int f[2];
        int g[2];
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

    void DFS0(int u, int from) {
        vertex[u].size = 1;
        vertex[u].dep = vertex[from].dep + 1;
        vertex[u].fa = from;
        vertex[u].f[1] = a[u];
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            DFS0(v, u);
            vertex[u].size += vertex[v].size;
            vertex[u].f[0] += std::max(vertex[v].f[0], vertex[v].f[1]);
            vertex[u].f[1] += vertex[v].f[0];
            if (vertex[v].size > vertex[vertex[u].hson].size) vertex[u].hson = v;
        }
        return;
    }

    int dfn;

    void DFS1(int u, int from, int top) {
        dfn++;
        dnf[dfn] = u;
        vertex[u].dfn = dfn;
        vertex[u].top = top;
        vertex[u].g[1] = a[u];
        vertex[vertex[u].top].end = u;
        if (vertex[u].hson) DFS1(vertex[u].hson, u, top);
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            if (v == vertex[u].hson) continue;
            DFS1(v, u, v);
            vertex[u].g[0] += std::max(vertex[v].f[0], vertex[v].f[1]);
            vertex[u].g[1] += vertex[v].f[0];
        }
        return;
    }

    void modify(int u, int val) {
        g[u].a[2][1] -= a[u];
        a[u] = val;
        g[u].a[2][1] += a[u];
        while (u) {
            Matrix bak = SGT.Query(1, 1, n, vertex[vertex[u].top].dfn, vertex[vertex[vertex[u].top].end].dfn);
            SGT.Modify(1, 1, n, vertex[u].dfn);
            Matrix upd = SGT.Query(1, 1, n, vertex[vertex[u].top].dfn, vertex[vertex[vertex[u].top].end].dfn);
            u = vertex[vertex[u].top].fa;
            int dif = std::max(upd.a[1][1], upd.a[2][1]) - std::max(bak.a[1][1], bak.a[2][1]);
            g[u].a[1][1] += dif;
            g[u].a[1][2] += dif;
            g[u].a[2][1] += upd.a[1][1] - bak.a[1][1];
        }
        return;
    }
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n - 1; i++) std::cin >> u >> v, graph::addEdge(u, v), graph::addEdge(v, u);
    graph::DFS0(1, 0);
    graph::DFS1(1, 0, 1);
    for (int i = 1; i <= n; i++) {
        g[i].a[1][1] = graph::vertex[i].g[0];
        g[i].a[1][2] = graph::vertex[i].g[0];
        g[i].a[2][1] = graph::vertex[i].g[1];
        g[i].a[2][2] = - inf;
    }
    SGT.Build(1, 1, n);
    for (int i = 1; i <= m; i++) {
        std::cin >> x >> y;
        graph::modify(x, y);
        Matrix res = SGT.Query(1, 1, n, 1, graph::vertex[graph::vertex[1].end].dfn);
        std::cout << std::max(res.a[1][1], res.a[2][1]) << '\n';
    }
    return 0;
}