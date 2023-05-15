#include <iostream>

const int maxN = 1e5;
const int maxM = 1e5;

int n, m;
int x, y, z;

struct DisjointSetUnion {
    struct Node {
        int fa;
    } node[2 * maxN + 10];

    void Init() {
        for (int i = 1; i <= 2 * n; i++) node[i].fa = i;
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

int ans;

int main() {
    std::cin >> n >> m;
    DSU.Init();
    for (int i = 1; i <= m; i++) {
        std::cin >> x >> y >> z;
        if (z & 1) {
            DSU.Union(n + x, y);
            DSU.Union(n + y, x);
        } else {
            DSU.Union(x, y);
            DSU.Union(n + x, n + y);
        }
    }
    for (int i = 1; i <= 2 * n; i++) {
        if (DSU.Find(i) == i) {
            ans++;
        }
    }
    std::cout << ans / 2 << '\n';
    return 0;
}