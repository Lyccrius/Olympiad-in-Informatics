#include <iostream>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef long long lxl;

const int maxN = 1e6;
const int maxM = 1e6;

int n, m;
int u[maxM + 10], v[maxM + 10];
lxl deg[maxN + 10];
lxl cnt;
lxl ans;

struct DisjointSetUnion {
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

    void Union(int u, int v) {
        u = Find(u);
        v = Find(v);
        if (u == v) return;
        node[u].fa = v;
        return;
    }
} DSU;

int main() {
    promote();
    std::cin >> n >> m;
    DSU.Init();
    for (int i = 1; i <= m; i++) {
        std::cin >> u[i] >> v[i];
        if (u[i] == v[i]) cnt++;
        else {
            DSU.Union(u[i], v[i]);
            deg[u[i]]++;
            deg[v[i]]++;
        }
    }
    for (int i = 1; i <= m; i++) {
        if (DSU.Find(u[i]) != DSU.Find(u[1])) {
            std::cout << 0 << '\n';
            return 0;
        }
    }
    ans += cnt * (cnt - 1) / 2;
    ans += cnt * (m - cnt);
    for (int i = 1; i <= n; i++) ans += deg[i] * (deg[i] - 1) / 2;
    std::cout << ans << '\n';
    return 0;
}