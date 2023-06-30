#include <iostream>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef long long lxl;

const int maxN = 1e5;
const int minA = -1e5;
const int maxA = 1e5;
const int logN = 17;
const lxl inf = 1e18;

int n;
int a[maxN + 10];
int b[maxN + 10];
int u, v;
lxl ans[maxN + 10];

struct Line {
    lxl k;
    lxl b;
} line[maxN + 10];

lxl calc(int i, lxl x) {
    return line[i].k * x + line[i].b;
}

struct SegmentTree {
    struct Node {
        int lson;
        int rson;
        int adv;
    } node[maxN * logN + 10];

    int ncnt;
    int root[maxN + 10];

    void Modify(int &u, int l, int r, int i) {
        if (!u) {
            u = ++ncnt;
            node[u].adv = i;
            return;
        }
        int mid = (l + r) / 2;
        if (calc(node[u].adv, mid) > calc(i, mid)) std::swap(node[u].adv, i);
        if (calc(node[u].adv, l) > calc(i, l)) Modify(node[u].lson, l, mid, i);
        if (calc(node[u].adv, r) > calc(i, r)) Modify(node[u].rson, mid + 1, r, i);
        return;
    }

    lxl Query(int u, int l, int r, int pos) {
        if (!u) return inf;
        int mid = (l + r) / 2;
        lxl ret = calc(node[u].adv, pos);
        if (l == r) return ret;
        if (pos <= mid) ret = std::min(ret, Query(node[u].lson, l, mid, pos));
        if (pos >= mid + 1) ret = std::min(ret, Query(node[u].rson, mid + 1, r, pos));
        return ret;
    }

    int Merge(int u, int v, int l, int r) {
        if (!u || !v) return u + v;
        int mid = (l + r) / 2;
        Modify(u, l, r, node[v].adv);
        if (l == r) return u;
        node[u].lson = Merge(node[u].lson, node[v].lson, l, mid);
        node[u].rson = Merge(node[u].rson, node[v].rson, mid + 1, r);
        return u;
    }
} SGT;

namespace graph {
    struct Vertex {
        int head;
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
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            DFS(v, u);
            SGT.root[u] = SGT.Merge(SGT.root[u], SGT.root[v], minA, maxA);
        }
        if (SGT.root[u]) ans[u] = SGT.Query(SGT.root[u], minA, maxA, a[u]);
        line[u].k = b[u];
        line[u].b = ans[u];
        SGT.Modify(SGT.root[u], minA, maxA, u);
        return;
    }
}

int main() {
    promote();
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) std::cin >> b[i];
    for (int i = 1; i <= n - 1; i++) std::cin >> u >> v, graph::addEdge(u, v), graph::addEdge(v, u);
    graph::DFS(1, 0);
    for (int i = 1; i <= n; i++) std::cout << ans[i] << ' ';
    return 0;
}