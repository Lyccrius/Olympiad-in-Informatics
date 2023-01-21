#include <iostream>
#include <vector>
#include <queue>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 5e4;
const int maxM = 1e6;
const int logN = 16;
const int inf = 1e9;

int n, m, s;
int op, u1, v1, u2, v2, u, v, w;

struct Portal {
    int u1, v1;
    int u2, v2;
    int w;
};
std::vector<Portal> portal;

namespace graph {
    struct Vertex {
        int vertex;
        int head;
        int dep;
        int dis;
        int vis;
        int fa;

        bool operator<(const Vertex &other) const {
            return dis > other.dis;
        }
    } vertex[maxN + 2 * (logN + 5) * maxN + maxM * 2 + 10];

    int vcnt;

    void addVertex(int &u) {
        u = ++vcnt;
        return;
    }

    struct Edge {
        int head;
        int next;
        int weight;
    } edge[maxM * 2 + (maxN * (logN + 5) * 4) + (maxM * (1 + 2 * (1 + (logN + 5) + 2 * (logN + 5) + 1))) + 10];

    int ecnt;

    void addEdge(int tail, int head, int weight) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].weight = weight;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        //printf("addEdgeing %d, %d, %d\n", tail, head, weight);
        return;
    }

    struct DisjointSetUnion {
        void Init() {
            for (int i = 1; i <= n; i++) vertex[i].fa = i;
            return;
        }

        int Find(int u) {
            if (vertex[u].fa == u) return u;
            return vertex[u].fa = Find(vertex[u].fa);
        }

        void Union(int u, int v) {
            u = Find(u);
            v = Find(v);
            vertex[u].fa = v;
            return;
        }
    } DSU;

    struct SparseTable {
        int f[maxN + 10][logN + 5];
        int i[maxN + 10][logN + 5];
        int o[maxN + 10][logN + 5];
    } ST;

    void init() {
        vcnt = n;
        DSU.Init();
        return;
    }

    void DFS(int u, int from) {
        //printf("DFSing %d from %d\n", u, from);
        ST.f[u][0] = from;
        vertex[u].dep = vertex[from].dep + 1;
        vertex[u].vis = true;
        addVertex(ST.i[u][0]); addEdge(ST.i[u][0], u, 0); addEdge(ST.i[u][0], from, 0);
        addVertex(ST.o[u][0]); addEdge(u, ST.o[u][0], 0); addEdge(from, ST.o[u][0], 0);
        for (int p = 1; p <= logN; p++) {
            ST.f[u][p] = ST.f[ST.f[u][p - 1]][p - 1];
            addVertex(ST.i[u][p]); addEdge(ST.i[u][p], ST.i[u][p - 1], 0); addEdge(ST.i[u][p], ST.i[ST.f[u][p - 1]][p - 1], 0);
            addVertex(ST.o[u][p]); addEdge(ST.o[u][p - 1], ST.o[u][p], 0); addEdge(ST.o[ST.f[u][p - 1]][p - 1], ST.o[u][p], 0);
        }
        //printf("vcnt = %d\n", vcnt);
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            if (v <= n) DFS(v, u);
        }
        return;
    }

    void Dijkstra(int s) {
        for (int i = 1; i <= vcnt; i++) vertex[i].vertex = i;
        for (int i = 1; i <= vcnt; i++) vertex[i].dis = inf;
        for (int i = 1; i <= vcnt; i++) vertex[i].vis = false;
        vertex[s].dis = 0;
        std::priority_queue<Vertex> q;
        q.push(vertex[s]);
        while (!q.empty()) {
            int u = q.top().vertex;
            q.pop();
            if (vertex[u].vis) continue;
            vertex[u].vis = true;
            //printf("Dijking %d, %d\n", u, vertex[u].dis);
            for (int e = vertex[u].head; e; e = edge[e].next) {
                int v = edge[e].head;
                int w = edge[e].weight;
                //printf("%d\n", v);
                if (vertex[v].dis > vertex[u].dis + w) {
                    vertex[v].dis = vertex[u].dis + w;
                    q.push(vertex[v]);
                }
            }
        }
        return;
    }

    void LCA1(int u, int v, int w) {
        //printf("LCA1(%d, %d, %d)\n", u, v, w);
        if (vertex[u].dep < vertex[v].dep) std::swap(u, v);
        addEdge(v, w, 0);
        for (int p = logN; p >= 0; p--) {
            if (vertex[ST.f[u][p]].dep >= vertex[v].dep) {
                addEdge(ST.o[u][p], w, 0);
                u = ST.f[u][p];
            }
        }
        if (u == v) return;
        for (int p = logN; p >= 0; p--) {
            if (ST.f[u][p] != ST.f[v][p]) {
                addEdge(ST.o[u][p], w, 0);
                addEdge(ST.o[v][p], w, 0);
                u = ST.f[u][p];
                v = ST.f[v][p];
            }
        }
        addEdge(ST.o[u][0], w, 0);
        return;
    }

    void LCA2(int u, int v, int w) {
        //printf("LCA2(%d, %d, %d)\n", u, v, w);
        if (vertex[u].dep < vertex[v].dep) std::swap(u, v);
        addEdge(w, v, 0);
        for (int p = logN; p >= 0; p--) {
            if (vertex[ST.f[u][p]].dep >= vertex[v].dep) {
                addEdge(w, ST.i[u][p], 0);
                u = ST.f[u][p];
            }
        }
        if (u == v) return;
        for (int p = logN; p >= 0; p--) {
            if (ST.f[u][p] != ST.f[v][p]) {
                addEdge(w, ST.i[u][p], 0);
                addEdge(w, ST.i[v][p], 0);
                u = ST.f[u][p];
                v = ST.f[v][p];
            }
        }
        addEdge(w, ST.i[u][0], 0);
        return;
    }

    void mian() {
        for (int i = 1; i <= n; i++) if (!vertex[i].vis) DFS(i, 0);
        //printf("%d\n", portal.size());
        for (int i = 0; i < portal.size(); i++) {
            LCA1(portal[i].u1, portal[i].v1, ++vcnt);
            LCA2(portal[i].u2, portal[i].v2, ++vcnt);
            addEdge(vcnt - 1, vcnt, portal[i].w);
        }
        Dijkstra(s);
        for (int i = 1; i <= n; i++) {
            if (vertex[i].dis == inf) std::cout << -1 << ' ';
            else std::cout << vertex[i].dis << ' ';
        }
        return;
    }
}

int main() {
    promote();
    std::cin >> n >> m >> s;
    graph::init();
    for (int i = 1; i <= m; i++) {
        std::cin >> op;
        if (op == 1) {
            std::cin >> u1 >> v1 >> u2 >> v2 >> w;
            if (graph::DSU.Find(u1) != graph::DSU.Find(v1) ||
                graph::DSU.Find(u2) != graph::DSU.Find(v2)) {
                continue;
            }
            portal.push_back((Portal) {u1, v1, u2, v2, w});
        } else {
            std::cin >> u >> v >> w;
            if (graph::DSU.Find(u) == graph::DSU.Find(v)) {
                continue;
            }
            //graph::addVertex(u, v);
            graph::addEdge(u, v, w);
            graph::addEdge(v, u, w);
            graph::DSU.Union(u, v);
        }
    }
    graph::mian();
    //std::cout << '\n' << graph::vcnt << '\n';
    return 0;
}