#include <iostream>
#include <vector>
#include <algorithm>

const int maxN = 1e6;

int t;
int n;
int i[maxN + 10], j[maxN + 10], e[maxN + 10];

struct DisjointSetUnion {
    int node[maxN * 2 + 10];

    void Init(int x) {
        for (int i = 0; i <= x; i++) node[i] = i;
        return;
    }

    int Find(int x) {
        if (node[x] == x) return x;
        return node[x] = Find(node[x]);
    }

    void Union(int x, int y) {
        x = Find(x);
        y = Find(y);
        if (x == y) return;
        node[x] = y;
        return;
    }
} DSU;

std::vector<int> range;

void mian() {
    std::cin >> n;
    bool ok = true;
    for (int k = 1; k <= n; k++) std::cin >> i[k] >> j[k] >> e[k];
    for (int k = 1; k <= n; k++) range.push_back(i[k]), range.push_back(j[k]);
    std::sort(range.begin(), range.end());
    DSU.Init(range.size());
    for (int k = 1; k <= n; k++) i[k] = std::lower_bound(range.begin(), range.end(), i[k]) - range.begin() + 1;
    for (int k = 1; k <= n; k++) j[k] = std::lower_bound(range.begin(), range.end(), j[k]) - range.begin() + 1;
    for (int k = 1; k <= n; k++) if (e[k] == 1) DSU.Union(i[k], j[k]);
    for (int k = 1; k <= n; k++) if (e[k] == 0) if (DSU.Find(i[k]) == DSU.Find(j[k])) ok = false;
    if (ok) std::cout << "YES\n";
    else std::cout << "NO\n";
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}