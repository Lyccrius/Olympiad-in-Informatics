#include <iostream>

typedef long long lxl;

const lxl maxN = 1e6;
const lxl maxM = 1e7;

lxl n;
lxl m;
lxl p;
lxl q;
lxl c[maxN + 10];

struct DisjointSetUnion {
    lxl node[maxN + 10];

    void Init() {
        for (lxl i = 1; i <= n; i++) node[i] = i;
        return;
    }

    lxl Find(lxl x) {
        if (node[x] == x) return x;
        return node[x] = Find(node[x]);
    }

    void Union(lxl x, lxl y) {
        x = Find(x);
        y = Find(y);
        node[x] = y;
        return;
    }
} DSU;

int main() {
    std::cin >> n;
    std::cin >> m;
    std::cin >> p;
    std::cin >> q;
    DSU.Init();
    for (lxl i = m; i >= 1; i--) {
        lxl l = ((i * p + q) % n) + 1;
        lxl r = ((i * q + p) % n) + 1;
        if (l > r) std::swap(l, r);
        while (l <= r) {
            if (DSU.Find(r) == r) c[r] = i;
            DSU.Union(r, r - 1);
            r = DSU.Find(r);
        }
    }
    for (int i = 1; i <= n; i++) std::cout << c[i] << '\n';
    return 0;
}