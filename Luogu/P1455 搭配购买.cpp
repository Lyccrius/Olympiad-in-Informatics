#include <iostream>
#include <vector>

const int maxN = 1e4;
const int maxW = 1e4;
const int maxM = 5e3;

int n, m, w;
int c[maxN + 10], d[maxN + 10];
int u[maxM + 10], v[maxM + 10];
int f[maxW + 10];
int ans;

struct DisjointSetUnion {
    struct Node {
        int c;
        int d;
        int fa;
    } node[maxN + 10];

    void Init() {
        for (int i = 1; i <= n; i++) node[i].c = c[i];
        for (int i = 1; i <= n; i++) node[i].d = d[i];
        for (int i = 1; i <= n; i++) node[i].fa = i;
        return;
    }

    int Find(int x) {
        if (node[x].fa == x) return x;
        return node[x].fa = Find(node[x].fa);
    }

    void Union(int x, int y) {
        x = Find(x);
        y = Find(y);
        if (x == y) return;
        node[x].fa = y;
        node[y].c += node[x].c;
        node[y].d += node[x].d;
        return;
    }
} DSU;

int main() {
    std::cin >> n >> m >> w;
    for (int i = 1; i <= n; i++) std::cin >> c[i] >> d[i];
    DSU.Init();
    std::vector<DisjointSetUnion::Node> vec;
    for (int i = 1; i <= m; i++) std::cin >> u[i] >> v[i], DSU.Union(u[i], v[i]);
    for (int i = 1; i <= n; i++) if (DSU.node[i].fa == i) vec.push_back(DSU.node[i]);
    for (int i = 0; i < vec.size(); i++) for (int j = w; j >= vec[i].c; j--) f[j] = std::max(f[j], f[j - vec[i].c] + vec[i].d);
    //for (int i = 0; i <= w; i++) ans = std::max(ans, f[i]);
    //std::cout << ans;
    std::cout << f[w];
    return 0;
}