#include <iostream>
#include <vector>

typedef std::vector<int> vic;

const int maxN = 5e5;
const int maxM = 5e5;
const int maxQ = 5e5;
const int maxK = 50;

int n, m, k, q;
int a, b;
int e, c;

struct Edge {
    int tail;
    int head;
    int c;
    vic q;
} edge[maxM + 10];

struct Query {
    int e;
    int c;
} query[maxQ + 10];

int ecnt;
int qcnt;

void addEdge(int a, int b) {
    ecnt++;
    edge[ecnt].tail = a;
    edge[ecnt].head = b;
    return;
}

void addQuery(int e, int c) {
    qcnt++;
    query[qcnt].e = e;
    query[qcnt].c = c;
    edge[e].q.push_back(qcnt);
    return;
}

struct DisjointSetUnion {
    struct Node {
        int fa;
        int size;
    } node[2 * maxN + 10];

    std::vector<Node> backup;

    void Init() {
        for (int i = 1; i <= 2 * n; i++) node[i].fa = i;
        for (int i = 1; i <= 2 * n; i++) node[i].size = 1;
        return;
    }

    int Find(int u) {
        if (node[u].fa == u) return u;
        return Find(node[u].fa);
    }

    void BackUp(int u) {
        backup.push_back(node[u]);
        return;
    }

    void Restore(int u) {
        node[node[u].fa].size -= node[u].size;
        node[u].fa = u;
        return;
    }

    void Union(int u, int v) {
        u = Find(u);
        v = Find(v);
        if (node[u].size > node[v].size) std::swap(u, v);
        if (u == v) return;
        BackUp(u);
        node[u].fa = v;
        node[v].size += node[u].size;
        return;
    }

    int Version() {
        return backup.size();
    }

    void RollBack(int ver) {
        while (Version() > ver) {
            Restore(backup.back().fa);
            backup.pop_back();
        }
        return;
    }
} DSU[maxK + 10];

struct SegmentTree {
    struct Node {
        vic q;
    } node[4 * maxQ + 10];

    void MakeTag(int u, int q) {
        node[u].q.push_back(q);
        return;
    }

    void Modify(int u, int l, int r, int s, int t, int q) {
        if (s > t) return;
        if (s <= l && r <= t) {
            MakeTag(u, q);
            return;
        }
        int mid = (l + r) / 2;
        if (s <= mid) Modify(2 * u, l, mid, s, t, q);
        if (t >= mid + 1) Modify(2 * u + 1, mid + 1, r, s, t, q);
        return;
    }

    void Build() {
        for (int i = 1; i <= m; i++) {
            edge[i].q.push_back(q + 1);
            for (int j = 0; j + 1 < edge[i].q.size(); j++) {
                Modify(1, 1, q, edge[i].q[j] + 1, edge[i].q[j + 1] - 1, edge[i].q[j]);
            }
        }
        return;
    }

    void Solve(int u, int l, int r) {
        int ver[maxK + 10];
        for (int i = 1; i <= k; i++) ver[i] = DSU[i].Version();
        for (auto i : node[u].q) {
            int e = query[i].e;
            int c = query[i].c;
            int u = edge[e].tail;
            int v = edge[e].head;
            DSU[c].Union(u, n + v);
            DSU[c].Union(n + u, v);
        }
        if (l == r) {
            int e = query[l].e;
            int c = query[l].c;
            int u = edge[e].tail;
            int v = edge[e].head;
            if (DSU[c].Find(u) != DSU[c].Find(v)) {
                std::cout << "YES" << '\n';
                edge[e].c = query[l].c;
            } else {
                std::cout << "NO" << '\n';
                query[l].c = edge[e].c;
            }
        } else {
            int mid = (l + r) / 2;
            Solve(2 * u, l, mid);
            Solve(2 * u + 1, mid + 1, r);
        }
        for (int i = 1; i <= k; i++) DSU[i].RollBack(ver[i]);
        return;
    }
} SGT;

int main() {
    std::cin >> n >> m >> k >> q;
    for (int i = 1; i <= m; i++) {
        std::cin >> a >> b;
        addEdge(a, b);
    }
    for (int i = 1; i <= q; i++) {
        std::cin >> e >> c;
        addQuery(e, c);
    }
    for (int i = 0; i <= k; i++) DSU[i].Init();
    SGT.Build();
    SGT.Solve(1, 1, q);
    return 0;
}