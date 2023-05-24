#include <iostream>
#include <string>

typedef std::string str;

const int maxN = 1e5;
const int maxQ = 1e5;
const int maxC = 1e5;
const int maxW = 1e4;
const int logN = 17;
const str CC = "CC";
const str CW = "CW";
const str QS = "QS";
const str QM = "QM";

int n, q;
int w, c;
int x, y;
str op;

namespace segmentTree {
    struct Node {
        int lson;
        int rson;
        int sum;
        int max;
    } node[maxN * logN + maxQ * logN + 10];

    int ncnt;

    void pushup(int u) {
        node[u].sum = node[node[u].lson].sum + node[node[u].rson].sum;
        node[u].max = std::max(node[node[u].lson].max, node[node[u].rson].max);
        return;
    }

    void add(int &u, int l, int r, int pos, int val) {
        if (!u) u = ++ncnt;
        if (l == r) {
            node[u].sum += val;
            node[u].max += val;
            return;
        }
        int mid = (l + r) / 2;
        if (pos <= mid) add(node[u].lson, l, mid, pos, val);
        if (pos >= mid + 1) add(node[u].rson, mid + 1, r, pos, val);
        pushup(u);
        return;
    }

    int askSum(int u, int l, int r, int s, int t) {
        if (!u) return 0;
        if (s <= l && r <= t) return node[u].sum;
        int mid = (l + r) / 2;
        if (t <= mid) return askSum(node[u].lson, l, mid, s, t);
        if (s >= mid + 1) return askSum(node[u].rson, mid + 1, r, s, t);
        return askSum(node[u].lson, l, mid, s, t) + askSum(node[u].rson, mid + 1, r, s, t);
    }

    int askMax(int u, int l, int r, int s, int t) {
        if (!u) return 0;
        if (s <= l && r <= t) return node[u].max;
        int mid = (l + r) / 2;
        if (t <= mid) return askMax(node[u].lson, l, mid, s, t);
        if (s >= mid + 1) return askMax(node[u].rson, mid + 1, r, s, t);
        return std::max(askMax(node[u].lson, l, mid, s, t), askMax(node[u].rson, mid + 1, r, s, t));
    }
}

struct SegmentTree {
    int root;

    void Add(int pos, int val) {
        segmentTree::add(root, 1, n, pos, val);
        return;
    }

    int AskSum(int l, int r) {
        return segmentTree::askSum(root, 1, n, l, r);
    }

    int AskMax(int l, int r) {
        return segmentTree::askMax(root, 1, n, l, r);
    }
} SGT[maxC + 10];

namespace graph {
    struct Vertex {
        int head;
        int size;
        int hson;
        int top;
        int dfn;
        int dep;
        int fa;
        int w, c;
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
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            DFS0(v, u);
            vertex[u].size += vertex[v].size;
            if (vertex[v].size > vertex[vertex[u].hson].size) vertex[u].hson = v;
        }
        return;
    }

    int dfn;

    void DFS1(int u, int from, int top) {
        dfn++;
        vertex[u].top = top;
        vertex[u].dfn = dfn;
        vertex[u].dep = vertex[from].dep + 1;
        vertex[u].fa = from;
        if (vertex[u].hson) DFS1(vertex[u].hson, u, top);
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            if (v == vertex[u].hson) continue;
            DFS1(v, u, v);
        }
        SGT[vertex[u].c].Add(vertex[u].dfn, vertex[u].w);
        return;
    }

    void CC(int u, int c) {
        SGT[vertex[u].c].Add(vertex[u].dfn, - vertex[u].w);
        vertex[u].c = c;
        SGT[vertex[u].c].Add(vertex[u].dfn, vertex[u].w);
        return;
    }

    void CW(int u, int w) {
        SGT[vertex[u].c].Add(vertex[u].dfn, - vertex[u].w);
        vertex[u].w = w;
        SGT[vertex[u].c].Add(vertex[u].dfn, vertex[u].w);
        return;
    }

    int QS(int u, int v) {
        int ret = 0;
        int t = vertex[u].c;
        while (vertex[u].top != vertex[v].top) {
            if (vertex[vertex[u].top].dep < vertex[vertex[v].top].dep) std::swap(u, v);
            ret += SGT[t].AskSum(vertex[vertex[u].top].dfn, vertex[u].dfn);
            u = vertex[vertex[u].top].fa;
        }
        if (vertex[u].dep > vertex[v].dep) std::swap(u, v);
        ret += SGT[t].AskSum(vertex[u].dfn, vertex[v].dfn);
        return ret;
    }

    int QM(int u, int v) {
        int ret = 0;
        int t = vertex[u].c;
        while (vertex[u].top != vertex[v].top) {
            if (vertex[vertex[u].top].dep < vertex[vertex[v].top].dep) std::swap(u, v);
            ret = std::max(ret, SGT[t].AskMax(vertex[vertex[u].top].dfn, vertex[u].dfn));
            u = vertex[vertex[u].top].fa;
        }
        if (vertex[u].dep > vertex[v].dep) std::swap(u, v);
        ret = std::max(ret, SGT[t].AskMax(vertex[u].dfn, vertex[v].dfn));
        return ret;
    }
}

int main() {
    std::cin >> n >> q;
    for (int i = 1; i <= n; i++) std::cin >> w >> c, graph::vertex[i].w = w, graph::vertex[i].c = c;
    for (int i = 1; i <= n - 1; i++) std::cin >> x >> y, graph::addEdge(x, y), graph::addEdge(y, x);
    graph::DFS0(1, 0);
    graph::DFS1(1, 0, 1);
    for (int i = 1; i <= q; i++) {
        std::cin >> op;
        if (op == CC) std::cin >> x >> c, graph::CC(x, c);
        if (op == CW) std::cin >> x >> w, graph::CW(x, w);
        if (op == QS) std::cin >> x >> y, std::cout << graph::QS(x, y) << '\n';
        if (op == QM) std::cin >> x >> y, std::cout << graph::QM(x, y) << '\n';
    }
    return 0;
}