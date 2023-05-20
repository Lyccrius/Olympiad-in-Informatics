#include <iostream>
#include <vector>

typedef std::vector<int> vic;

const int maxN = 4e4;
const int maxW = 1e3;
const int maxK = 2e4;

int n;
int u, v, w;
int k;
int ans;

struct SegmentTree {
    struct Node {
        int val;
    } node[4 * maxK + 10];

    void PushUp(int u) {
        node[u].val = node[2 * u].val + node[2 * u + 1].val;
        return;
    }

    void Add(int u, int l, int r, int pos, int val) {
        if (l == r) {
            node[u].val += val;
            return;
        }
        int mid = (l + r) / 2;
        if (pos <= mid) Add(2 * u, l, mid, pos, val);
        if (pos >= mid + 1) Add(2 * u + 1, mid + 1, r, pos, val);
        PushUp(u);
        return;
    }

    int Ask(int u, int l, int r, int s, int t) {
        if (s > t) return 0;
        if (s <= l && r <= t) return node[u].val;
        int mid = (l + r) / 2;
        if (t <= mid) return Ask(2 * u, l, mid, s, t);
        if (s >= mid + 1) return Ask(2 * u + 1, mid + 1, r, s, t);
        return Ask(2 * u, l, mid, s, t) + Ask(2 * u + 1, mid + 1, r, s, t);
    }
} SGT;

namespace graph {
    struct Vertex {
        int head;
        int part;
        int size;
        int vis;
        int dis;
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

    int root;
    int tot;
    vic t;
    vic q;

    void calcSize(int u, int from) {
        vertex[u].part = 0;
        vertex[u].size = 1;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            int w = edge[e].weight;
            if (v == from) continue;
            if (vertex[v].vis) continue;
            calcSize(v, u);
            vertex[u].part = std::max(vertex[u].part, vertex[v].size);
            vertex[u].size += vertex[v].size;
        }
        vertex[u].part = std::max(vertex[u].part, tot - vertex[u].size);
        if (vertex[root].part > vertex[u].part) root = u;
        return;
    }

    void calcDist(int u, int from) {
        t.push_back(vertex[u].dis);
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            int w = edge[e].weight;
            if (v == from) continue;
            if (vertex[v].vis) continue;
            vertex[v].dis = vertex[u].dis + w;
            calcDist(v, u);
        }
        return;
    }

    void divide(int u, int from) {
        SGT.Add(1, 0, maxK, 0, 1);
        q.push_back(0);
        vertex[u].vis = true;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            int w = edge[e].weight;
            if (v == from) continue;
            if (vertex[v].vis) continue;
            vertex[v].dis = w;
            calcDist(v, u);
            for (auto i : t) if (i <= k) ans += SGT.Ask(1, 0, maxK, std::max(0, 1 - i), std::max(0, k - i));
            for (auto i : t) if (i <= k) SGT.Add(1, 0, maxK, i, 1);
            for (auto i : t) if (i <= k) q.push_back(i);
            t.clear();
        }
        for (auto i : q) SGT.Add(1, 0, maxK, i, -1);
        q.clear();
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            int w = edge[e].weight;
            if (v == from) continue;
            if (vertex[v].vis) continue;
            tot = vertex[v].size;
            root = 0;
            calcSize(v, u);
            calcSize(root, 0);
            divide(root, 0);
        }
        return;
    }
}

int main() {
    std::cin >> n;
    for (int i = 1; i <= n - 1; i++) std::cin >> u >> v >> w, graph::addEdge(u, v, w), graph::addEdge(v, u, w);
    std::cin >> k;
    graph::root = 0;
    graph::tot = n;
    graph::vertex[0].part = maxN;
    graph::calcSize(1, 0);
    graph::calcSize(graph::root, 0);
    graph::divide(graph::root, 0);
    std::cout << ans << '\n';
    return 0;
}