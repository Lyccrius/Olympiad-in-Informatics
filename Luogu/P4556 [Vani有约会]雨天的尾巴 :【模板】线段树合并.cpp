#include <iostream>

const int maxN = 1e5;
const int maxZ = 1e5;
const int logN = 17;
const int logZ = 17;

int n, m;
int a, b;
int x, y, z;
int ans[maxN + 10];

struct SegmentTree {
    struct Node {
        int lson;
        int rson;
        int val;
        int res;
    } node[4 * maxN * logZ + 10];

    int ncnt;
    int root[maxN + 10];

    int Build() {
        return ++ncnt;
    }

    void PushUp(int u) {
        if (node[node[u].lson].val > 0 || node[node[u].rson].val > 0) {
            if (node[node[u].lson].val >= node[node[u].rson].val) {
                node[u].val = node[node[u].lson].val;
                node[u].res = node[node[u].lson].res;
            } else {
                node[u].val = node[node[u].rson].val;
                node[u].res = node[node[u].rson].res;
            }
        }
        return;
    }

    int Merge(int u, int v, int l, int r) {
        if (!u || !v) return u ^ v;
        if (l == r) {
            node[u].val += node[v].val;
            if (node[u].val > 0) node[u].res = l;
            else node[u].res = 0;
            return u;
        }
        int mid = (l + r) / 2;
        node[u].lson = Merge(node[u].lson, node[v].lson, l, mid);
        node[u].rson = Merge(node[u].rson, node[v].rson, mid + 1, r);
        PushUp(u);
        return u;
    }

    void Add(int &u, int l, int r, int pos, int val) {
        if (!u) u = Build();
        if (l == r) {
            node[u].val += val;
            if (node[u].val > 0) node[u].res = pos;
            else node[u].res = 0;
            return;
        }
        int mid = (l + r) / 2;
        if (pos <= mid) Add(node[u].lson, l, mid, pos, val);
        if (pos >= mid + 1) Add(node[u].rson, mid + 1, r, pos, val);
        PushUp(u);
        return;
    }

    int Query(int u, int l, int r) {
        if (node[u].val)
        return node[u].res;
        else return 0;
    }
} SGT;

namespace graph {
    struct Vertex {
        int head;
        int dep;
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
    } edge[maxN * 2 + 10];
    
    int ecnt;

    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    struct SparseTable {
        struct Node {
            int f;
        } node[maxN + 10][logN + 5];
    } ST;

    void DFS1(int u, int from) {
        ST.node[u][0].f = from;
        vertex[u].dep = vertex[from].dep + 1;
        for (int p = 1; p <= logN; p++) ST.node[u][p].f = ST.node[ST.node[u][p - 1].f][p - 1].f;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            DFS1(v, u);
        }
        return;
    }

    void DFS2(int u, int from) {
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            DFS2(v, u);
            SGT.root[u] = SGT.Merge(SGT.root[u], SGT.root[v], 1, maxZ);
        }
        ans[u] = SGT.Query(SGT.root[u], 1, maxZ);
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
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i < n; i++) {
        std::cin >> a >> b;
        graph::addEdge(a, b);
        graph::addEdge(b, a);
    }
    graph::DFS1(1, 0);
    for (int i = 1; i <= m; i++) {
        std::cin >> x >> y >> z;
        int f = graph::LCA(x, y);
        int g = graph::ST.node[f][0].f;
        SGT.Add(SGT.root[x], 1, maxZ, z, 1);
        SGT.Add(SGT.root[y], 1, maxZ, z, 1);
        SGT.Add(SGT.root[f], 1, maxZ, z, - 1);
        SGT.Add(SGT.root[g], 1, maxZ, z, - 1);
    }
    graph::DFS2(1, 0);
    for (int i = 1; i <= n; i++) std::cout << ans[i] << '\n';
    return 0;
}