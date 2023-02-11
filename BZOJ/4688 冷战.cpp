#include <iostream>
#include <algorithm>

const int maxN = 5e5;

int N, M;
int op, u, v;
int ans;
int cnt;

struct DisjointSetUnion {
    struct Node {
        int fa;
        int dep;
        int size;
        int res;
    } node[maxN + 10];

    void Init() {
        for (int i = 1; i <= maxN; i++) node[i].fa = i;
        for (int i = 1; i <= maxN; i++) node[i].size = 1;
        return;
    }

    int Find(int u) {
        if (node[u].fa == u) return u;
        int ret = Find(node[u].fa);
        node[u].dep = node[node[u].fa].dep + 1;
        return ret;
    }

    void Union(int u, int v, int rank) {
        u = Find(u);
        v = Find(v);
        if (u == v) return;
        if (node[u].size > node[v].size) std::swap(u, v);
        node[u].fa = v;
        node[v].size += node[u].size;
        node[u].res = rank;
        return;
    }

    int Query(int u, int v) {
        int fu = Find(u);
        int fv = Find(v);
        if (fu != fv) return 0;
        int ret = 0;
        if (node[u].dep < node[v].dep) std::swap(u, v);
        while (node[u].dep > node[v].dep) ret = std::max(ret, node[u].res), u = node[u].fa;
        while (u != v) ret = std::max(ret, std::max(node[u].res, node[v].res)), u = node[u].fa, v = node[v].fa;
        return ret;
    }
} DSU;

int main() {
    DSU.Init();
    std::cin >> N >> M;
    while (M--) {
        std::cin >> op >> u >> v;
        u ^= ans;
        v ^= ans;
        if (op == 0) DSU.Union(u, v, ++cnt);
        if (op == 1) std::cout << (ans = DSU.Query(u, v)) << '\n';
    }
    return 0;
}