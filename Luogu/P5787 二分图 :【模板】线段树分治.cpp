#include <iostream>
#include <algorithm>
#include <vector>

const int maxN = 1e5;
const int maxK = 1e5;
const int maxM = 2e5;

int n, m, k;
int x, y, l, r;

struct Edge {
    int tail;
    int head;

    Edge(int u, int v) {
        tail = u;
        head = v;
        return;
    }
};

struct DisjointSetUnion {
    struct Node {
        int fa;
        int dep;
    } node[2 * maxN + 10];

    std::vector<Node> backup;

    void Init() {
        for (int i = 1; i <= 2 * n; i++) node[i].fa = i;
        for (int i = 1; i <= 2 * n; i++) node[i].dep = 1;
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
            node[u] = backup.back();
            backup.pop_back();
        }
        return;
    }

    void Union(int u, int v) {
        u = Find(u);
        v = Find(v);
        if (node[u].dep > node[v].dep) std::swap(u, v);
        BackUp(u);
        node[u].fa = v;
        node[v].dep = std::max(node[v].dep, node[u].dep + 1);
        return;
    }
} DSU;

struct SegmentTree {
    struct Node {
        std::vector<Edge> edge;
    } node[4 * maxK + 10];

    void MakeTag(int u, int tail, int head) {
        node[u].edge.push_back(Edge(tail, head));
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
        bool ok = true;
        int bak = DSU.backup.size();
        for (auto edge : node[u].edge) {
            int u = edge.tail;
            int v = edge.head;
            int fu = DSU.Find(u);
            int fv = DSU.Find(v);
            if (fu == fv) {
                ok = false;
                for (int i = l; i <= r; i++) {
                    std::cout << "No" << '\n';
                }
                break;
            }
            DSU.Union(n + u, v);
            DSU.Union(u, n + v);
        }
        if (ok) {
            if (l == r) {
                std::cout << "Yes" << '\n';
            } else {
                int mid = (l + r) / 2;
                Solve(2 * u, l, mid);
                Solve(2 * u + 1, mid + 1, r);
            }
        }
        DSU.Restore(bak);
        return;
    }
} SGT;

int main() {
    std::cin >> n >> m >> k;
    DSU.Init();
    for (int i = 1; i <= m; i++) {
        std::cin >> x >> y >> l >> r;
        SGT.Modify(1, 1, k, l + 1, r, x, y);
    }
    SGT.Solve(1, 1, k);
    return 0;
}