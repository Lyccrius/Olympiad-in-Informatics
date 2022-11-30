#include <cstdio>
#include <algorithm>
#include <vector>

const int maxN = 1e6 + 10;

typedef std::pair<long long, int> pli;

int n, T;
int Num[maxN];
long long lastans = 0;
int a, b, x, y;
int l, r;
int m;
std::vector<int> pos[maxN];
pli res[maxN];
long long sco;
int tot;

bool cmp(int x, int y) {
    if (res[x].second == -1) return true;
    long long resX = res[x].first * res[y].second;
    long long resY = res[y].first * res[x].second;
    return resX <= resY;
}

struct DisjointSet {
    struct Node {
        int fa;
        long long size;
    } node[maxN];

    int Find(int x) {
        if (x == node[x].fa) return x;
        return node[x].fa = Find(node[x].fa);
    }

    void Union(int x, int y) {
        x = Find(x);
        y = Find(y);
        if (x == y) return;
        sco -= node[x].size * node[x].size + node[y].size * node[y].size;
        node[x].size += node[y].size;
        node[y].fa = x;
        sco += node[x].size * node[x].size;
        tot--;
        return;
    }
} djs;

void mian() {
    scanf("%d%d%d%d", &a, &b, &x, &y);
    l = (a * lastans + x - 1) % n + 1;
    r = (b * lastans + y - 1) % n + 1;
    if (l > r) std::swap(l, r);
    sco = -1;
    x = -1;
    for (int i = l; i <= r; i++) if (res[i].first != -1) {
        res[0] = std::make_pair(sco, x);
        if (cmp(0, i)) sco = res[i].first, x = res[i].second;
    }
    printf("%lld %d\n", sco, x);
    printf("%d %d %lld\n", l, r, lastans);
    lastans = sco * x % n;
    return;
}

int main() {
    scanf("%d%d", &n, &T);
    for (int i = 1; i <= n; i++) scanf("%d", &Num[i]), pos[Num[i]].push_back(i), m = std::max(m, Num[i]);
    for (int i = 1; i <= n; i++) djs.node[i].fa = i;
    for (int i = 1; i <= n; i++) djs.node[i].size = 1;
    for (int i = 1; i <= n; i++) res[i].first = -1;
    for (int i = 1; i <= n; i++) res[i].second = -1;
    for (int x = 1; x <= m; x++) {
        for (int i = 0; i < pos[x].size(); i++) sco += 1 * 1;
        for (int i = 0; i < pos[x].size(); i++) tot++;
        for (int i = 0; i < pos[x].size(); i++) if (pos[x][i] != 1 && Num[pos[x][i] - 1] <= x) djs.Union(pos[x][i], pos[x][i] - 1);
        for (int i = 0; i < pos[x].size(); i++) if (pos[x][i] != n && Num[pos[x][i] + 1] <= x) djs.Union(pos[x][i], pos[x][i] + 1);
        res[0] = std::make_pair(sco, x);
        if (cmp(tot, 0)) res[tot].first = sco, res[tot].second = x;
    }
    while (T--) mian();
    return 0;
}