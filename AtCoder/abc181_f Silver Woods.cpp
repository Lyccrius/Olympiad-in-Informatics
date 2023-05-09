#include <iostream>

typedef double dbl;

const int maxN = 100;
const dbl eps = 1e-4;

int n;
dbl x[maxN + 10];
dbl y[maxN + 10];

struct DisjointSetUnion {
    struct Node {
        int fa;
    } node[maxN + 10];

    void Init() {
        for (int i = 0; i <= n + 1; i++) node[i].fa = i;
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

dbl dis2(int i, int j) {
    dbl dx = std::abs(x[i] - x[j]);
    dbl dy = std::abs(y[i] - y[j]);
    return dx * dx + dy * dy;
}

bool check(dbl d) {
    DSU.Init();
    for (int i = 1; i <= n; i++) if (100 - y[i] < d) DSU.Union(n + 1, i);
    for (int i = 1; i <= n; i++) if (y[i] + 100 < d) DSU.Union(0, i);
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (dis2(i, j) < d * d) {
                DSU.Union(i, j);
            }
        }
    }
    return DSU.Find(0) != DSU.Find(n + 1);
}

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> x[i] >> y[i];
    dbl l = 0;
    dbl r = 100;
    while (r - l > eps) {
        dbl mid = (l + r) / 2;
        if (check(mid * 2)) l = mid;
        else r = mid;
    }
    std::cout << l << '\n';
    return 0;
}