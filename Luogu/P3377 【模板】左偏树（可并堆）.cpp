#include <iostream>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 1e5;
const int maxM = 1e5;

int n, m;
int a[maxN + 10];
int b[maxN + 10];
int op, x, y;

struct DisjointSetUnion {
    struct Node {
        int fa;
    } node[maxN + 10];

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

struct LeftistTree {
    struct Node {
        int lson;
        int rson;
        int dis;
        int val;
    } node[maxN + 10];

    int ncnt;
    int root[maxN + 10];

    void Insert(int u, int val) {
        if (u) u = ++ncnt;
        node[u].val = val;
        return;
    }

    int Merge(int u, int v) {
        if (!u) return v;
        if (!v) return u;
        if (node[u].val > node[v].val) std::swap(u, v);
        if (node[u].val == node[v].val && u > v) std::swap(u, v); 
        node[u].rson = Merge(node[u].rson, v);
        if (node[node[u].lson].dis < node[node[u].rson].dis) std::swap(node[u].lson, node[u].rson);
        node[u].dis = node[node[u].rson].dis + 1;
        return u;
    }

    int Top(int u) {
        return node[u].val;
    }

    void Pop(int &u) {
        b[u] = true;
        u = Merge(node[u].lson, node[u].rson);
        return;
    }
} LT;

int main() {
    promote();
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        DSU.node[i].fa = i;
        LT.root[i] = i;
        LT.Insert(LT.root[i], a[i]);
    }
    for (int i = 1; i <= m; i++) {
        std::cin >> op;
        if (op == 1) {
            std::cin >> x >> y;
            if (b[x]) continue;
            if (b[y]) continue;
            int fx = DSU.Find(x);
            int fy = DSU.Find(y);
            if (fx == fy) continue;
            int root = LT.Merge(LT.root[fx], LT.root[fy]);
            LT.root[fx] = root;
            LT.root[fy] = root;
            DSU.Union(fx, fy);
        } else if (op == 2) {
            std::cin >> x;
            if (b[x]) {
                std::cout << - 1 << '\n';
                continue;
            }
            int fx = DSU.Find(x);
            int res = LT.Top(LT.root[fx]);
            std::cout << LT.Top(LT.root[fx]) << '\n';
            LT.Pop(LT.root[fx]);
        }
    }
    return 0;
}