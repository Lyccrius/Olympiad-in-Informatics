#include <cstdio>
#include <algorithm>
#include <queue>

const int inf = 1e9;
const int maxN = 2e5;
const int maxM = 4e5;
const int logN = 17;

int T;

int n, m;
int u, v, l, a;
int Q, K, S;
int v0, p0;
int lastans;

namespace graph {
    struct Edge {
        int tail;
        int head;
        int next;
        int l;
        int a;

        bool operator<(const Edge &other) const {
            return a > other.a;
        }
    } edge[maxM * 2 + maxN * 2 + 10];

    int ecnt;

    struct Vertex {
        int vertex;
        int weight;
        int head;
        int dep;
        int dis;
        int vis;
        int fa;

        bool operator<(const Vertex &other) const {
            return dis > other.dis;
        }
    } vertex[maxN * 2 + 10];

    int vcnt;

    struct DisjointSetUnion {
        int Find(int u) {
            if (vertex[u].fa == u) return u;
            return vertex[u].fa = Find(vertex[u].fa);
        }

        void Union(int u, int v) {
            u = Find(u);
            v = Find(v);
            if (u == v) return;
            vertex[u].fa = v;
            return;
        }
    } DSU;

    struct SpareTable {
        int table[maxN * 2 + 10][logN + 1 + 10];
    } ST;

    void init() {
        vcnt = n;
        ecnt = 0;
        for (int u = 1; u <= n * 2; u++) {
            vertex[u].vertex = u;
            vertex[u].weight = -1;
            vertex[u].head = 0;
            vertex[u].dis = inf;
            vertex[u].vis = false;
            vertex[u].fa = u;
        }
        lastans = 0;
        return;
    }

    void addEdge(int tail, int head, int l, int a) {
        ecnt++;
        edge[ecnt].tail = tail;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        edge[ecnt].l = l;
        edge[ecnt].a = a;
        vertex[tail].head = ecnt;
        return;
    }

    void addVertex(int u, int v, int a) {
        vcnt++;
        vertex[vcnt].weight = a;
        addEdge(vcnt, u, 0, 0);
        addEdge(vcnt, v, 0, 0);
        DSU.Union(u, vcnt);
        DSU.Union(v, vcnt);
        return;
    }

    void Dijkstra(int s) {
        std::priority_queue<Vertex> q;
        vertex[s].dis = 0;
        q.push(vertex[s]);
        while (!q.empty()) {
            int u = q.top().vertex;
            q.pop();
            if (vertex[u].vis) continue;
            vertex[u].vis = true;
            for (int e = vertex[u].head; e; e = edge[e].next) {
                int v = edge[e].head;
                int w = edge[e].l;
                if (vertex[v].dis > vertex[u].dis + w) {
                    vertex[v].dis = vertex[u].dis + w;
                    q.push(vertex[v]);
                }
            }
        }
        return;
    }

    void Kruskal() {
        int connected = 0;
        std::sort(edge + 1, edge + ecnt + 1);
        for (int e = 1; e <= ecnt; e++) {
            int u = edge[e].tail;
            int v = edge[e].head;
            int a = edge[e].a;
            u = DSU.Find(u);
            v = DSU.Find(v);
            if (u == v) continue;
            addVertex(u, v, a);
            connected++;
            if (connected == n - 1) break;
        }
    }

    void DFS(int u, int from) {
        vertex[u].dep = vertex[from].dep + 1;
        ST.table[u][0] = from;
        for (int p = 1; p <= logN + 1; p++) ST.table[u][p] = ST.table[ST.table[u][p - 1]][p - 1];
        if (vertex[u].weight == -1) return;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            DFS(v, u);
            vertex[u].dis = std::min(vertex[u].dis, vertex[v].dis);
        }
        return;
    }

    int query(int v, int p) {
        for (int i = logN + 1; i >= 0; i--) {
            if ((vertex[v].dep - (1 << i) > 0) && (vertex[ST.table[v][i]].weight > p)) {
                v = ST.table[v][i];
            }
        }
        return vertex[v].dis;
    }
}

void mian() {
    scanf("%d%d", &n, &m);
    graph::init();
    while (m--) scanf("%d%d%d%d", &u, &v, &l, &a), graph::addEdge(u, v, l, a), graph::addEdge(v, u, l, a);
    graph::Dijkstra(1);
    graph::Kruskal();
    graph::DFS(graph::vcnt, 0);
    scanf("%d%d%d", &Q, &K, &S);
    while (Q--) {
        scanf("%d%d", &v0, &p0);
        int v = (v0 + K * lastans - 1) % n + 1;
        int p = (p0 + K * lastans) % (S + 1);
        lastans = graph::query(v, p);
        printf("%d\n", lastans);
    }
    return;
}

int main() {
    scanf("%d", &T);
    while (T--) mian();
    return 0;
}