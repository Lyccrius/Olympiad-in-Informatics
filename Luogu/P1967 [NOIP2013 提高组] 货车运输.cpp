#include <iostream>
#include <algorithm>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 1e4;
const int maxM = 5e4;
const int logN = 15;

int n, m;
int x, y, z;
int q;

namespace graph {
    struct Vertex {
        int fa;
        int dep;
        int head;
        int weight;
    } vertex[maxN * 2 + 10];

    int vcnt;

    struct Edge {
        int tail;
        int head;
        int next;
        int weight;

        bool operator<(const Edge &other) const {
            return weight > other.weight;
        }
    } edge[maxM + maxN * 2 + 10];
    
    int ecnt;

    struct SpareTable {
        int f[maxN * 2 + 10][logN + 5];
    } ST;

    struct DisjointSetUnion {
        int Find(int u) {
            if (u == vertex[u].fa) return u;
            return vertex[u].fa = Find(vertex[u].fa);
        }

        void Union(int u, int v) {
            u = Find(u);
            v = Find(v);
            vertex[u].fa = v;
            return;
        }
    } DSU;

    void addEdge(int tail, int head, int weight) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].tail = tail;
        edge[ecnt].weight = weight;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    void addVertex(int u, int v, int w) {
        vcnt++;
        vertex[vcnt].weight = w;
        vertex[vcnt].fa = vcnt;
        addEdge(vcnt, u, 0);
        addEdge(vcnt, v, 0);
        DSU.Union(u, vcnt);
        DSU.Union(v, vcnt);
        //printf("addVertex(%d, %d, %d): %d\n", u, v, w, vcnt);
        return;
    }

    void DFS(int u, int from) {
        vertex[u].dep = vertex[from].dep + 1;
        ST.f[u][0] = from;
        //printf("DFSing %d from %d\n", u, from);
        for (int p = 1; p <= logN; p++) ST.f[u][p] = ST.f[ST.f[u][p - 1]][p - 1];
        if (vertex[u].weight == -1) return;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            DFS(v, u);
            //if (vertex[v].weight != -1) vertex[u].weight = std::min(vertex[u].weight, vertex[v].weight);
        }
        //printf("%d %d\n", u, vertex[u].weight);
        return;
    }

    void Kruscal() {
        vcnt = n;
        int cnt = 0;
        std::sort(edge + 1, edge + ecnt + 1);
        for (int i = 1; i <= n; i++) vertex[i].fa = i;
        for (int i = 1; i <= n; i++) vertex[i].weight = -1;
        for (int i = 1; i <= ecnt; i++) {
            int u = edge[i].tail;
            int v = edge[i].head;
            int w = edge[i].weight;
            u = DSU.Find(u);
            v = DSU.Find(v);
            if (u == v) continue;
            addVertex(u, v, w);
            cnt++;
            if (cnt == n - 1) break;
        }
        for (int i = vcnt; i > 0; i--) if (!vertex[i].dep) DFS(i, 0);
        return;
    }

    int LCA(int u, int v) {
        if (vertex[u].dep < vertex[v].dep) std::swap(u, v);
        for (int p = logN; p >= 0; p--) {
            if (vertex[ST.f[u][p]].dep >= vertex[v].dep) {
                u = ST.f[u][p];
            }
        }
        if (u == v) return vertex[u].weight;
        for (int p = logN; p >= 0; p--) {
            if (ST.f[u][p] != ST.f[v][p]) {
                u = ST.f[u][p];
                v = ST.f[v][p];
            }
        }
        return vertex[ST.f[u][0]].weight;
    }
}

struct DisjointSetUnion {
    int fa[maxN + 10];

    int Find(int x) {
        if (x == fa[x]) return x;
        else return fa[x] = Find(fa[x]);
    }

    void Union(int x, int y) {
        x = Find(x);
        y = Find(y);
        if (x == y) return;
        fa[x] = y;
        return;
    }
} DSU;

int main() {
    promote();
    //freopen("P1967_8.in", "r", stdin);
    //freopen("P1967_8.out", "w", stdout);
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) DSU.fa[i] = i;
    for (int i = 1; i <= m; i++) std::cin >> x >> y >> z, graph::addEdge(x, y, z), DSU.Union(x, y);
    graph::Kruscal();
    std::cin >> q;
    for (int i = 1; i <= q; i++) {
        std::cin >> x >> y;
        if (DSU.Find(x) != DSU.Find(y)) {
            std::cout << -1 << '\n';
            continue;
        }
        //printf("%d, %d\n", DSU.Find(x), DSU.Find(y));
        std::cout << graph::LCA(x, y) << '\n';
    }
    return 0;
}