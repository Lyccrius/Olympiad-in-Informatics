#include <iostream>

const int maxN = 2e6;
const int maxM = 1e6;

int n, m;
int u, v;
int vis[maxN + 10];
int ideg[maxN + 10];
int odeg[maxN + 10];
int size[maxN + 10];
int ans;

struct DisjointSetUnion {
    struct Node {
        int fa;
    } node[maxN + 10];

    DisjointSetUnion() {
        for (int i = 1; i <= maxN; i++) node[i].fa = i;
        return;
    }

    int Find(int u) {
        if (node[u].fa == u) return u;
        return node[u].fa = Find(node[u].fa);
    }

    void Union(int u, int v) {
        u = Find(u);
        v = Find(v);
        node[u].fa = v;
        return;
    }
} DSU;

int main() {
    std::cin >> m;
    for (int i = 1; i <= m; i++) {
        std::cin >> u >> v;
        DSU.Union(u, v);
        vis[u] = true;
        vis[v] = true;
        odeg[u]++;
        ideg[v]++;
        n = std::max(n, u);
        n = std::max(n, v);
    }
    for (int i = 1; i <= n; i++) if (vis[i]) size[DSU.Find(i)] += std::abs(ideg[i] - odeg[i]);
    for (int i = 1; i <= n; i++) if (vis[i]) if (DSU.Find(i) == i) ans += std::max(1, size[i] / 2);
    std::cout << ans + m << '\n';
    return 0;
}