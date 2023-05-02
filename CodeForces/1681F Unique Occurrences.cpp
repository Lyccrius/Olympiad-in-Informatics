#include <iostream>
#include <vector>

typedef long long lxl;

const int maxN = 5e5;

int n;
int u, v, x;

struct Edge {
    int tail;
    int head;

    Edge(int u, int v) {
        tail = u;
        head = v;
        return;
    }
};

std::vector<Edge> edges[maxN + 10];

struct DisjointSetUnion {
    struct Node {
        int fa;
        int size;
    } node[maxN + 10];

    std::vector<Node> backup;

    void Init() {
        for (int i = 1; i <= n; i++) node[i].fa = i;
        for (int i = 1; i <= n; i++) node[i].size = 1;
        return;
    }

    int Find(int u) {
        if (node[u].fa == u) return u;
        return Find(node[u].fa);
    }

    void BackUp(int u) {
        backup.push_back(node[u]);
        return;
    }

    void Restore(int tot) {
        while (backup.size() > tot) {
            int u = backup.back().fa;
            node[node[u].fa].size -= node[u].size;
            node[u].fa = u;
            backup.pop_back();
        }
        return;
    }

    void Union(int u, int v) {
        u = Find(u);
        v = Find(v);
        if (u == v) return;
        if (node[u].size > node[v].size) std::swap(u, v);
        BackUp(u);
        node[u].fa = v;
        node[v].size += node[u].size;
        return;
    }

    int Version() {
        return backup.size();
    }
} DSU;

lxl ans;

struct SegmentTree {
    struct Node {
        std::vector<Edge> edges;
    } node[4 * maxN + 10];

    void MakeTag(int u, int tail, int head) {
        node[u].edges.push_back(Edge(tail, head));
        return;
    }

    void Modify(int u, int l, int r, int s, int t, int tail, int head) {
        if (s > t) return;
        if (s <= l && r <= t) {
            MakeTag(u, tail, head);
            return;
        }
        int mid = (l + r) / 2;
        if (s <= mid) Modify(2 * u, l, mid, s, t, tail, head);
        if (t >= mid + 1) Modify(2 * u + 1, mid + 1, r, s, t, tail, head);
        return;
    }

    void Solve(int u, int l, int r) {
        int bak = DSU.Version();
        for (auto edge : node[u].edges) {
            int u = edge.tail;
            int v = edge.head;
            DSU.Union(u, v);
        }
        if (l == r) {
            for (auto edge : edges[l]) {
                int u = edge.tail;
                int v = edge.head;
                u = DSU.Find(u);
                v = DSU.Find(v);
                ans += 1ll * DSU.node[u].size * DSU.node[v].size;
            }
        } else {
            int mid = (l + r) / 2;
            Solve(2 * u, l, mid);
            Solve(2 * u + 1, mid + 1, r);
        }
        DSU.Restore(bak);
        return;
    }
} SGT;

int main() {
    std::cin >> n;
    DSU.Init();
    for (int i = 1; i < n; i++) {
        std::cin >> u >> v >> x;
        edges[x].push_back(Edge(u, v));
        SGT.Modify(1, 1, n, 1, x - 1, u, v);
        SGT.Modify(1, 1, n, x + 1, n, u, v);
    }
    SGT.Solve(1, 1, n);
    std::cout << ans << '\n';
    return 0;
}