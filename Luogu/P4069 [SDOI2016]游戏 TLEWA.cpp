#include <iostream>

#define int long long

typedef long long lxl;

const int maxN = 1e5;
const int maxM = 1e5;
const int maxA = 1e4;
const lxl inf = 123456789123456789;

int n, m;
int u, v, w;
int op, s, t, a, b;

namespace graph {
    struct Vertex {
        int head;
        int hson;
        int size;
        int top;
        int dep;
        int dfn;
        lxl dis;
        int fa;
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
        int weight;
    } edge[2 * maxN + 10];

    int ecnt;

    void addEdge(int tail, int head, int weight) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        edge[ecnt].weight = weight;
        vertex[tail].head = ecnt;
        return;
    }

    void DFS0(int u, int from) {
        vertex[u].size = 1;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            int w = edge[e].weight;
            if (v == from) continue;
            vertex[v].dep = vertex[u].dep + 1;
            vertex[v].dis = vertex[u].dis + w;
            vertex[v].fa = u;
            DFS0(v, u);
            vertex[u].size += vertex[v].size;
            if (vertex[v].size > vertex[vertex[u].hson].size) vertex[u].hson = v;
        }
        return;
    }

    int dfn;
    int dnf[maxN + 10];

    void DFS1(int u, int from, int top) {
        dfn++;
        vertex[u].dfn = dfn;
        vertex[u].top = top;
        dnf[dfn] = u;
        if (vertex[u].hson) DFS1(vertex[u].hson, u, top);
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            if (v == vertex[u].hson) continue;
            DFS1(v, u, v);
        }
        return;
    }

    int LCA(int u, int v) {
        while (vertex[u].top != vertex[v].top) {
            if (vertex[vertex[u].top].dep < vertex[vertex[v].top].dep) std::swap(u, v);
            u = vertex[vertex[u].top].fa;
        }
        if (vertex[u].dep < vertex[v].dep) return u;
        else return v;
    }
}

struct Segment {
    lxl k, b;

    Segment() {
        b = inf;
    }
} segment[2 * maxM + 10];

int tot;

lxl calc(int i, int x) {
    //printf("calc(%d, %d) = ", i, x);
    x = graph::vertex[graph::dnf[x]].dis;
    //printf("%d\n", segment[i].b + segment[i].k * x);
    return segment[i].b + segment[i].k * x;
}

struct SegmentTree {
    struct Node {
        int i;
        lxl res;

        Node() {
            i = 0;
            res = inf;
        }
    } node[4 * maxN + 10];

    void PushUp(int u, int l, int r) {
        node[u].res = std::min(calc(node[u].i, l), calc(node[u].i, r));
        node[u].res = std::min(node[u].res, node[2 * u].res);
        node[u].res = std::min(node[u].res, node[2 * u + 1].res);
        //printf("res[%d], [%d, %d] = %d (%d)\n", u, l, r, node[u].res, node[u].i);
        return;
    }

    void MakeTag(int u, int l, int r, int i) {
        int mid = (l + r) / 2;
        if (calc(i, mid) < calc(node[u].i, mid)) std::swap(node[u].i, i);
        if (calc(i, l) < calc(node[u].i, l)) MakeTag(2 * u, l, mid, i);
        if (calc(i, r) < calc(node[u].i, r)) MakeTag(2 * u + 1, mid + 1, r, i);
        PushUp(u, l, r);
        return;
    }

    void Add(int u, int l, int r, int s, int t, int i) {
        if (s <= l && r <= t) {
            MakeTag(u, l, r, i);
            PushUp(u, l, r);
            return;
        }
        int mid = (l + r) / 2;
        if (s <= mid) Add(2 * u, l, mid, s, t, i);
        if (t >= mid + 1) Add(2 * u + 1, mid + 1, r, s, t, i);
        PushUp(u, l, r);
        return;
    }

    lxl Ask(int u, int l, int r, int s, int t) {
        if (s <= l && r <= t) {
            //printf("Ask(%d, [%d, %d], [%d, %d]) = %d\n", u, l, r, s, t, node[u].res);
            return node[u].res;
        }
        int mid = (l + r) / 2;
        //lxl ret = node[u].res;
        lxl ret = std::min(calc(node[u].i, std::max(l, s)), calc(node[u].i, std::min(r, t)));
        if (s <= mid) ret = std::min(ret, Ask(2 * u, l, mid, s, t));
        if (t >= mid + 1) ret = std::min(ret, Ask(2 * u + 1, mid + 1, r, s, t));
        //printf("Ask(%d, [%d, %d], [%d, %d]) = %d\n", u, l, r, s, t, ret);
        return ret;
    }
} SGT;

void add(int u, int v, int i) {
    using namespace graph;
    while (vertex[u].top != vertex[v].top) {
        SGT.Add(1, 1, n, vertex[vertex[u].top].dfn, vertex[u].dfn, i);
        u = vertex[vertex[u].top].fa;
    }
    SGT.Add(1, 1, n, vertex[v].dfn, vertex[u].dfn, i);
    return;
}

lxl ask(int u, int v) {
    using namespace graph;
    lxl ret = inf;
    while (vertex[u].top != vertex[v].top) {
        if (vertex[vertex[u].top].dep < vertex[vertex[v].top].dep) std::swap(u, v);
        ret = std::min(ret, SGT.Ask(1, 1, n, vertex[vertex[u].top].dfn, vertex[u].dfn));
        u = vertex[vertex[u].dfn].fa;
    }
    if (vertex[u].dfn > vertex[v].dfn) std::swap(u, v);
    ret = std::min(ret, SGT.Ask(1, 1, n, vertex[u].dfn, vertex[v].dfn));
    return ret;
}

void Alice() {
    std::cin >> s >> t >> a >> b;
    int r = graph::LCA(s, t);
    tot++;
    segment[tot].k = -a;
    segment[tot].b = 1ll * a * graph::vertex[s].dis + b;
    add(s, r, tot);
    tot++;
    segment[tot].k = a;
    segment[tot].b = 1ll * a * (graph::vertex[s].dis - graph::vertex[r].dis - graph::vertex[r].dis) + b;
    add(t, r, tot);
    return;
}

void Bob() {
    std::cin >> s >> t;
    std::cout << ask(s, t) << '\n';
    return;
}

signed main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n - 1; i++) std::cin >> u >> v >> w, graph::addEdge(u, v, w), graph::addEdge(v, u, w);
    graph::DFS0(1, 0);
    graph::DFS1(1, 0, 1);
    for (int i = 1; i <= m; i++) {
        std::cin >> op;
        if (op == 1) Alice();
        if (op == 2) Bob();
    }
    return 0;
}