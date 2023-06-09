#include <iostream>

typedef char chr;

const int maxN = 1e5;
const int maxQ = 1e5;

int n, q;
chr op[maxQ + 10];
int x[maxQ + 10], y[maxQ + 10];

struct SegmentTree {
    struct Node {
        int val;
        int tag;
    } node[4 * maxN + 10];

    void MakeTag(int u, int val) {
        node[u].val += val;
        node[u].tag += val;
        return;
    }

    void PushDown(int u) {
        if (!node[u].tag) return;
        MakeTag(2 * u, node[u].tag);
        MakeTag(2 * u + 1, node[u].tag);
        node[u].tag = 0;
        return;
    }

    void PushUp(int u) {
        node[u].val = node[2 * u].val + node[2 * u + 1].val;
        return;
    }

    void Build(int u, int l, int r) {
        if (l == r) {
            node[u].val = 1;
            return;
        }
        int mid = (l + r) / 2;
        Build(2 * u, l, mid);
        Build(2 * u + 1, mid + 1, r);
        PushUp(u);
        return;
    }

    void Add(int u, int l, int r, int s, int t, int val) {
        if (s <= l && r <= t) {
            MakeTag(u, val);
            return;
        }
        int mid = (l + r) / 2;
        PushDown(u);
        if (s <= mid) Add(2 * u, l, mid, s, t, val);
        if (t >= mid + 1) Add(2 * u + 1, mid + 1, r, s, t, val);
        PushUp(u);
        return;
    }
    
    int Ask(int u, int l, int r, int pos) {
        if (l == r) return node[u].val;
        int mid = (l + r) / 2;
        PushDown(u);
        if (pos <= mid) return Ask(2 * u, l, mid, pos);
        if (pos >= mid + 1) return Ask(2 * u + 1, mid + 1, r, pos);
    }
} SGT;

struct DisjiontSetUnion {
    struct Node {
        int fa;
    } node[maxN + 10];

    void Init() {
        for (int i = 1; i <= n; i++) node[i].fa = i;
        return;
    }

    int Find(int u) {
        if (node[u].fa == u) return u;
        return node[u].fa = Find(node[u].fa);
    }
} DSU;

namespace graph {
    struct Vertex {
        int head;
        int hson;
        int size;
        int top;
        int dfn;
        int dep;
        int fa;
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

    int dfn;

    void DFS0(int u, int from) {
        vertex[u].fa = from;
        vertex[u].dep = vertex[from].dep + 1;
        vertex[u].size = 1;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            DFS0(v, u);
            vertex[u].size += vertex[v].size;
            if (vertex[v].size > vertex[vertex[u].hson].size) vertex[u].hson = v;
        }
        return;
    }

    void DFS1(int u, int from, int top) {
        dfn++;
        vertex[u].dfn = dfn;
        vertex[u].top = top;
        if (vertex[u].hson) DFS1(vertex[u].hson, u, top);
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            if (v == vertex[u].hson) continue;
            DFS1(v, u, v);
        }
        return;
    }

    void init() {
        for (int i = 1; i <= n; i++) if (!vertex[i].dep) DFS0(i, 0);
        for (int i = 1; i <= n; i++) if (!vertex[i].dfn) DFS1(i, 0, i);
        SGT.Build(1, 1, n);
        DSU.Init();
        return;
    }

    void add(int u, int v) {
        if (vertex[u].fa == v) std::swap(u, v);
        int fu = DSU.Find(u);
        int sv = SGT.Ask(1, 1, n, vertex[v].dfn);
        DSU.node[v].fa = fu;
        while (vertex[u].top != vertex[fu].top) {
            if (vertex[vertex[u].top].dep < vertex[vertex[fu].top].dep) std::swap(u, fu);
            SGT.Add(1, 1, n, vertex[vertex[u].top].dfn, vertex[u].dfn, sv);
            u = vertex[vertex[u].top].fa;
        }
        if (vertex[u].dep < vertex[fu].dep) std::swap(u, fu);
        SGT.Add(1, 1, n, vertex[fu].dfn, vertex[u].dfn, sv);
        return;
    }

    void query(int u, int v) {
        if (vertex[u].fa == v) std::swap(u, v);
        int fu = DSU.Find(u);
        int sg = SGT.Ask(1, 1, n, vertex[fu].dfn);
        int sv = SGT.Ask(1, 1, n, vertex[v].dfn);
        std::cout << 1ll * (sg - sv) * sv << '\n';
        return;
    }
}

int main() {
    std::cin >> n >> q;
    for (int i = 1; i <= q; i++) {
        std::cin >> op[i] >> x[i] >> y[i];
        if (op[i] == 'A') graph::addEdge(x[i], y[i]), graph::addEdge(y[i], x[i]);
    }
    graph::init();
    for (int i = 1; i <= q; i++) {
        if (op[i] == 'A') graph::add(x[i], y[i]);
        if (op[i] == 'Q') graph::query(x[i], y[i]);
    }
    return 0;
}