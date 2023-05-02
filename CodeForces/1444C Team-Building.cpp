#include <iostream>
#include <algorithm>
#include <vector>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef long long lxl;

const int maxN = 5e5;
const int maxM = 5e5;
const int maxK = 5e5;

int n, m, k;
int c[maxN + 10];
int a, b;
int d[maxK + 10];
int p[maxK + 10];
lxl ans;

struct Edge {
    int tail;
    int head;

    Edge(int u, int v) {
        tail = u;
        head = v;
        return;
    }

    bool operator<(const Edge &other) const {
        return c[head] < c[other.head];
    }
};

std::vector<Edge> edges[maxK + 10];

struct DisjointSetUnion {
    struct Node {
        int fa;
        int size;
    } node[2 * maxN + 10];

    std::vector<Node> backup;

    void Init() {
        for (int i = 1; i <= 2 * n; i++) node[i].fa = i;
        for (int i = 1; i <= 2 * n; i++) node[i].size = 1;
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

    void Restore(int u) {
        node[node[u].fa].size -= node[u].size;
        node[u].fa = u;
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

    void RollBack(int ver) {
        while (backup.size() > ver) {
            Restore(backup.back().fa);
            backup.pop_back();
        }
        return;
    }
} DSU;

int main() {
    promote();
    std::cin >> n >> m >> k;
    DSU.Init();
    for (int i = 1; i <= n; i++) std::cin >> c[i];
    for (int i = 1; i <= m; i++) {
        std::cin >> a >> b;
        if (c[a] > c[b]) std::swap(a, b);
        if (c[a] == c[b]) {
            if (DSU.Find(a) == DSU.Find(b)) {
                d[c[a]] = true;
            } else {
                DSU.Union(a, n + b);
                DSU.Union(n + a, b);
            }
        } else {
            edges[c[a]].push_back(Edge(a, b));
        }
    }
    int bak = DSU.backup.size();
    for (int i = k; i >= 1; i--) p[i] = p[i + 1] + 1 - d[i];
    for (int i = 1; i <= k; i++) {
        if (d[i]) continue;
        std::sort(edges[i].begin(), edges[i].end());
        ans += p[i + 1];
        for (int j = 0; j < edges[i].size(); j++) {
            if ((j == 0) || (j && c[edges[i][j - 1].head] != c[edges[i][j].head])) {
                DSU.RollBack(bak);
            }
            int u = edges[i][j].tail;
            int v = edges[i][j].head;
            int fu = DSU.Find(u);
            int fv = DSU.Find(v);
            if (d[c[u]]) continue;
            if (d[c[v]]) continue;
            if (fu == fv) {
                ans--;
                while (j + 1 < edges[i].size() && c[edges[i][j].head] == c[edges[i][j + 1].head]) j++;
            } else {
                DSU.Union(u, n + v);
                DSU.Union(n + u, v);
            }
        }
    }
    std::cout << ans << '\n';
    return 0;
}