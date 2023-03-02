#include <iostream>
#include <algorithm>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 5e5;
const int maxM = 5e5;

int n;
int u, v;
int m;
int op;

namespace graph {
    struct Vertex {
        int head;
        int size;
        int dfn;
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

    int dfn;

    void DFS(int u, int from) {
        dfn++;
        vertex[u].dfn = dfn;
        vertex[u].size = 1;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            DFS(v, u);
            vertex[u].size += vertex[v].size;
        }
        return;
    }
}

struct SegmentTree {
    struct Node {
        int val;
        int tag;
    } node[maxN * 4 + 10];

    void MakeTag(int u, int tag) {
        node[u].val = tag;
        node[u].tag = tag;
        return;
    }

    void PushUp(int u) {
        node[u].val = std::max(node[u * 2].val, node[u * 2 + 1].val);
        return;
    }

    void PushDown(int u) {
        if (!node[u].tag) return;
        MakeTag(u * 2, node[u].tag);
        MakeTag(u * 2 + 1, node[u].tag);
        node[u].tag = 0;
        return;
    }

    void Modify(int u, int l, int r, int s, int t, int val) {
        if (s <= l && r <= t) {
            MakeTag(u, val);
            return;
        }
        PushDown(u);
        int mid = (l + r) / 2;
        if (s <= mid) Modify(u * 2, l, mid, s, t, val);
        if (t >= mid + 1) Modify(u * 2 + 1, mid + 1, r, s, t, val);
        PushUp(u);
        return;
    }

    int Query(int u, int l, int r, int s, int t) {
        if (s <= l && r <= t) {
            return node[u].val;
        }
        PushDown(u);
        int mid = (l + r) / 2;
        if (t <= mid) return Query(u * 2, l, mid, s, t);
        if (s >= mid + 1) return Query(u * 2 + 1, mid + 1, r, s, t);
        return std::max(Query(u * 2, l, mid, s, t), Query(u * 2 + 1, mid + 1, r, s, t));
    }
} SGT1, SGT2;

int main() {
    std::cin >> n;
    for (int i = 1; i < n; i++) {
        std::cin >> u >> v;
        graph::addEdge(u, v);
        graph::addEdge(v, u);
    }
    graph::DFS(1, 0);
    std::cin >> m;
    for (int i = 1; i <= m; i++) {
        std::cin >> op >> u;
        if (op == 1) {
            SGT1.Modify(1, 1, n, graph::vertex[u].dfn, graph::vertex[u].dfn + graph::vertex[u].size - 1, i);
        } else if (op == 2) {
            SGT2.Modify(1, 1, n, graph::vertex[u].dfn, graph::vertex[u].dfn, i);
        } else if (op == 3) {
            int a = SGT1.Query(1, 1, n, graph::vertex[u].dfn, graph::vertex[u].dfn);
            int b = SGT2.Query(1, 1, n, graph::vertex[u].dfn, graph::vertex[u].dfn + graph::vertex[u].size - 1);
            if (a > b) {
                std::cout << 1 << '\n';
            } else {
                std::cout << 0 << '\n';
            }
        }
    }
    return 0;
}