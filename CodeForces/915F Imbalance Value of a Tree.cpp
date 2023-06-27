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

const int maxN = 1e6;

int n;
int a[maxN + 10];
int u, v;
lxl ans;

struct Edge {
    int u, v;
    int w;
    
    bool operator<(const Edge &other) const {
        return w < other.w;
    }
};

std::vector<Edge> edge;

struct DisjointSetUnion {
    struct Node {
        int fa;
        int size;
    } node[maxN + 10];

    void init() {
        for (int i = 1; i <= n; i++) node[i].fa = i;
        for (int i = 1; i <= n; i++) node[i].size = 1;
        return;
    }

    int find(int u) {
        if (node[u].fa == u) return u;
        return node[u].fa = find(node[u].fa);
    }
} dsu;

int main() {
    promote();
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n - 1; i++) std::cin >> u >> v, edge.push_back((Edge) {u, v, 0});
    dsu.init();
    for (auto &e : edge) e.w = std::max(a[e.u], a[e.v]);
    std::sort(edge.begin(), edge.end());
    for (auto e : edge) {
        int fu = dsu.find(e.u);
        int fv = dsu.find(e.v);
        if (fu != fv) {
            ans += 1ll * e.w * dsu.node[fu].size * dsu.node[fv].size;
            dsu.node[fu].fa = fv;
            dsu.node[fv].size += dsu.node[fu].size;
        }
    }
    dsu.init();
    for (auto &e : edge) e.w = std::min(a[e.u], a[e.v]);
    std::sort(edge.begin(), edge.end());
    std::reverse(edge.begin(), edge.end());
    for (auto e : edge) {
        int fu = dsu.find(e.u);
        int fv = dsu.find(e.v);
        if (fu != fv) {
            ans -= 1ll * e.w * dsu.node[fu].size * dsu.node[fv].size;
            dsu.node[fu].fa = fv;
            dsu.node[fv].size += dsu.node[fu].size;
        }
    }
    std::cout << ans << '\n';
    return 0;
}