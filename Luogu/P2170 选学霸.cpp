#include <iostream>
#include <vector>

const int maxN = 2e5;
const int maxM = 2e5;

int n, m, k;
int x, y;
int f[maxN + 10];
int ans;

struct DisjointSetUnion {
    struct Node {
        int fa;
        int size;
    } node[maxN + 10];

    void Init() {
        for (int i = 1; i <= n; i++) node[i].fa = i;
        for (int i = 1; i <= n; i++) node[i].size = 1;
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
        if (node[x].size > node[y].size) std::swap(x, y);
        node[x].fa = y;
        node[y].size += node[x].size;
        return;
    }
} DSU;

int main() {
    std::cin >> n >> m >> k;
    DSU.Init();
    for (int i = 1; i <= k; i++) std::cin >> x >> y, DSU.Union(x, y);
    std::vector<DisjointSetUnion::Node> vec;
    f[0] = true;
    for (int i = 1; i <= n; i++) if (DSU.Find(i) == i) vec.push_back(DSU.node[i]);
    for (int i = 0; i < vec.size(); i++) for (int j = n; j >= vec[i].size; j--) f[j] |= f[j - vec[i].size];
    for (int i = 0; i <= n; i++) if (f[i]) if (std::abs(m - i) < std::abs(m - ans) || (std::abs(m - i) == std::abs(m - ans) && i < ans)) ans = i;
    std::cout << ans;
    return 0;
}