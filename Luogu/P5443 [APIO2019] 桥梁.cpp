#include <iostream>
#include <algorithm>
#include <vector>

const int maxN = 5e4;
const int maxM = 1e5;
const int maxQ = 1e5;
const int sqrQ = 1289;

int n, m;
int u, v, d;
int q;
int t, a, b;

struct Edge {
    int i, u, v, d;

    bool operator<(const Edge &other) const {
        return d > other.d;
    }
} edge[maxM + 10];

int ecnt;

void addEdge(int u, int v, int d) {
    ecnt++;
    edge[ecnt].i = ecnt;
    edge[ecnt].u = u;
    edge[ecnt].v = v;
    edge[ecnt].d = d;
    return;
}

struct Query {
    int i, t, a, b;

    bool operator<(const Query &other) const {
        return b > other.b;
    }
} query[maxQ + 10];

int qcnt;

void addQuery(int t, int a, int b) {
    qcnt++;
    query[qcnt].i = qcnt;
    query[qcnt].t = t;
    query[qcnt].a = a;
    query[qcnt].b = b;
    return;
}

int ans[maxQ + 10];

std::vector<Edge> es;
std::vector<Query> ms;
std::vector<Query> qs;

struct DisjiontSetUnion {
    struct Node {
        int fa;
        int size;
    } node[maxN + 10];

    std::vector<int> backup;

    int Version() {
        return backup.size();
    }

    void BackUp(int u) {
        backup.push_back(u);
        return;
    }

    void Restore() {
        int u = backup.back();
        backup.pop_back();
        node[node[u].fa].size -= node[u].size;
        node[u].fa = u;
        return;
    }

    void RollBack(int ver) {
        while (Version() > ver) {
            Restore();
        }

        return;
    }

    void Init() {
        backup.clear();
        for (int i = 1; i <= n; i++) node[i].fa = i;
        for (int i = 1; i <= n; i++) node[i].size = 1;
        return;
    }

    int Find(int u) {
        if (node[u].fa == u) return u;
        return Find(node[u].fa);
    }

    void Union(int u, int v, int b) {
        u = Find(u);
        v = Find(v);
        if (u == v) return;
        if (node[u].size > node[v].size) std::swap(u, v);
        if (b) BackUp(u);
        node[u].fa = v;
        node[v].size += node[u].size;
        return;
    }

    int Query(int u) {
        u = Find(u);
        return node[u].size;
    }
} DSU;

int tag[maxM + 10];
int vis[maxM + 10];

void solve(int l, int r) {
    es.clear();
    ms.clear();
    qs.clear();
    DSU.Init();
    for (int i = 1; i <= m; i++) tag[i] = false;
    for (int i = 1; i <= m; i++) es.push_back(edge[i]);
    for (int i = l; i <= r; i++) if (query[i].t == 1) tag[query[i].a] = true;
    for (int i = l; i <= r; i++) if (query[i].t == 1) ms.push_back(query[i]);
    for (int i = l; i <= r; i++) if (query[i].t == 2) qs.push_back(query[i]);
    std::sort(es.begin(), es.end());
    std::sort(qs.begin(), qs.end());
    int ie = 0;
    int iq = 0;
    while (iq < qs.size()) {
        while (ie < es.size() && es[ie].d >= qs[iq].b) {
            if (tag[es[ie].i] == false) DSU.Union(es[ie].u, es[ie].v, 0);
            ie++;
        }
        for (int im = ms.size() - 1; im >= 0; im--) vis[ms[im].a] = false;
        for (int im = ms.size() - 1; im >= 0; im--) {
            if (vis[ms[im].a]) continue;
            if (ms[im].i > qs[iq].i) continue;
            if (ms[im].b >= qs[iq].b) DSU.Union(edge[ms[im].a].u, edge[ms[im].a].v, true);
            vis[ms[im].a] = true;
        }
        for (int im = ms.size() - 1; im >= 0; im--) {
            if (vis[ms[im].a]) continue;
            if (ms[im].i < qs[iq].i) break;
            if (edge[ms[im].a].d >= qs[iq].b) DSU.Union(edge[ms[im].a].u, edge[ms[im].a].v, true);
        }
        ans[qs[iq].i] = DSU.Query(qs[iq].a);
        DSU.RollBack(0);
        iq++;
    }
    for (int i = l; i <= r; i++) if (query[i].t == 1) edge[query[i].a].d = query[i].b;
    return;
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        std::cin >> u >> v >> d;
        addEdge(u, v, d);
    }
    std::cin >> q;
    for (int i = 1; i <= q; i++) {
        std::cin >> t >> a >> b;
        addQuery(t, a, b);
    }
    for (int l = 1, r; l <= q; l = r + 1) {
        r = std::min(q, l + sqrQ - 1);
        solve(l, r);
    }
    for (int i = 1; i <= q; i++) if (query[i].t == 2) std::cout << ans[i] << '\n';
    return 0;
}