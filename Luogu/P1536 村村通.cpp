#include <cstdio>

const int maxN = 1000 + 10;

int n, m;
int u, v;

struct DisjointSetUnion {
    struct Node {
        int fa;
    } node[maxN];

    void Init() {
        for (int i = 1; i <= n; i++) node[i].fa = i;
        return;
    }

    int Find(int x) {
        if (x == node[x].fa) return x;
        return node[x].fa = Find(node[x].fa);
    }

    void Union(int x, int y) {
        x = Find(x);
        y = Find(y);
        if (x == y) return;
        node[x].fa = y;
        return;
    }
};

void mian() {
    DisjointSetUnion DSU;
    DSU.Init();
    int cnt = 0;
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &u, &v);
        DSU.Union(u, v);
    }
    for (int i = 1; i <= n; i++) if (DSU.Find(i) == i) cnt++;
    printf("%d\n", cnt - 1);
    return;
}

int main() {
    while (scanf("%d", &n) && n) scanf("%d", &m), mian();
    return 0;
}