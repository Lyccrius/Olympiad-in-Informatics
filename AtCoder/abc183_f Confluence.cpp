#include <iostream>
#include <map>
#include <set>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef std::map<int, int> mii;
typedef std::set<int> sit;

const int maxN = 2e5;
const int maxQ = 2e5;

int n, q;
int c[maxN + 10];
int op;
int a, b;
int x, y;

struct DisjointSetUnion {
    struct Node {
        int fa;
        mii m;
        sit s;
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
        if (node[u].s.size() > node[v].s.size()) std::swap(u, v);
        node[u].fa = v;
        for (auto w : node[u].s) {
            node[v].s.insert(w);
            node[v].m[w] += node[u].m[w];
        }
        return;
    }
} DSU;

int main() {
    promote();
    std::cin >> n >> q;
    DSU.Init();
    for (int i = 1; i <= n; i++) std::cin >> c[i];
    for (int i = 1; i <= n; i++) DSU.node[i].m[c[i]] = 1;
    for (int i = 1; i <= n; i++) DSU.node[i].s.insert(c[i]);
    for (int i = 1; i <= q; i++) {
        std::cin >> op;
        if (op == 1) {
            std::cin >> a >> b;
            DSU.Union(a, b);
        } else if (op == 2) {
            std::cin >> x >> y;
            std::cout << DSU.node[DSU.Find(x)].m[y] << '\n';
        }
    }
    return 0;
}