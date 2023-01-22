#include <iostream>
#include <algorithm>
#include <queue>
#include <map>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef long long lxl;

const int maxN = 1e5;
const int maxM = 3e5;
const int logN = 17;
const int inf = 1e9;
const lxl lnf = 1e18;

int N, M;
int x, y, z;
lxl ans;

namespace graph {
    struct Vertex {
        int fa;
        int dep;
        int vis;
        int head;
    } vertex[maxN + 10];

    struct Edge {
        int tail;
        int head;
        int next;
        int id;
        lxl weight;
        int choose;

        bool operator<(const Edge &other) const {
            return weight > other.weight;
        }
    } edge[maxM * 2 + 10];
    
    int ecnt;

    void addEdge(int tail, int head, lxl weight) {
        ecnt++;
        edge[ecnt].id = ecnt;
        edge[ecnt].tail = tail;
        edge[ecnt].head = head;
        edge[ecnt].weight = weight;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

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

        void Init() {
            for (int i = 1; i <= N; i++) vertex[i].fa = i;
            return;
        }
    } DSU;

    struct SparseTable {
        int f[maxN + 10][logN + 5];
        lxl fir[maxN + 10][logN + 5];
        lxl sec[maxN + 10][logN + 5];
    } ST;

    lxl sum;

    void Kruscal() {
        std::priority_queue<Edge> q;
        DSU.Init();
        int tot = 0;
        for (int i = 1; i <= ecnt; i++) q.push(edge[i]);
        while (!q.empty()) {
            int u = q.top().tail;
            int v = q.top().head;
            int w = q.top().weight;
            int e = q.top().id;
            q.pop();
            if (DSU.Find(u) == DSU.Find(v)) continue;
            DSU.Union(u, v);
            sum += w;
            edge[e].choose = true;
            edge[e ^ 1].choose = true;
            tot++;
            if (tot == N - 1) break;
        }
        //printf("%lld\n", sum);
        return;
    }

    void DFS(int u) {
        //printf("DFSing %d from %d\n", u, ST.f[u][0]);
        vertex[u].dep = vertex[ST.f[u][0]].dep + 1;
        for (int p = 1; p <= logN; p++) {
            ST.f[u][p] = ST.f[ST.f[u][p - 1]][p - 1];
            if (ST.fir[u][p - 1] == ST.fir[ST.f[u][p - 1]][p - 1]) {
                ST.fir[u][p] = ST.fir[u][p - 1];
                ST.sec[u][p] = std::max(ST.sec[u][p - 1], ST.sec[ST.f[u][p - 1]][p - 1]);
            }
            if (ST.fir[u][p - 1] > ST.fir[ST.f[u][p - 1]][p - 1]) {
                ST.fir[u][p] = ST.fir[u][p - 1];
                ST.sec[u][p] = std::max(ST.sec[u][p - 1], ST.fir[ST.f[u][p - 1]][p - 1]);
            }
            if (ST.fir[u][p - 1] < ST.fir[ST.f[u][p - 1]][p - 1]) {
                ST.fir[u][p] = ST.fir[ST.f[u][p - 1]][p - 1];
                ST.sec[u][p] = std::max(ST.fir[u][p - 1], ST.sec[ST.f[u][p - 1]][p - 1]);
            }
        }
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            int w = edge[e].weight;
            if (v == ST.f[u][0]) continue;
            if (!edge[e].choose) continue;
            ST.f[v][0] = u;
            ST.fir[v][0] = w;
            DFS(v);
        }
        return;
    }

    int LCA(int u, int v) {
        if (vertex[u].dep < vertex[v].dep) std::swap(u, v);
        for (int p = logN; p >= 0; p--) if (vertex[ST.f[u][p]].dep >= vertex[v].dep) u = ST.f[u][p];
        if (u == v) return u;
        for (int p = logN; p >= 0; p--) if (ST.f[u][p] != ST.f[v][p]) u = ST.f[u][p], v = ST.f[v][p];
        return ST.f[u][0];
    }

    lxl calc(int u, int v, int w) {
        //printf("calcing %d, %d, %d\n", u, v, w);
        int g = LCA(u, v);
        //printf("LCA(%d, %d) = %d\n", u, v, g);
        lxl fir = 0;
        lxl sec = 0;
        for (int p = logN; p >= 0; p--) {
            if (vertex[ST.f[u][p]].dep >= vertex[g].dep) {
                if (fir == ST.fir[u][p]) sec = std::max(sec, ST.sec[u][p]);
                if (fir > ST.fir[u][p]) sec = std::max(sec, ST.fir[u][p]);
                if (fir < ST.fir[u][p]) sec = std::max(fir, ST.sec[u][p]), fir = ST.fir[u][p];
                u = ST.f[u][p];
            }
            if (vertex[ST.f[v][p]].dep >= vertex[g].dep) {
                if (fir == ST.fir[v][p]) sec = std::max(sec, ST.sec[v][p]);
                if (fir > ST.fir[v][p]) sec = std::max(sec, ST.fir[v][p]);
                if (fir < ST.fir[v][p]) sec = std::max(fir, ST.sec[v][p]), fir = ST.fir[v][p];
                v = ST.f[v][p];
            }
        }
        if (w != fir) {
            //printf("ret = %d\n", sum - fir + w);
            return sum - fir + w;
        }
        if (sec != w) {
            //printf("ret = %d\n", sum - sec + w);
            return sum - sec + w;
        }
        //printf("fir = %d, sec = %d\n", fir, sec);
        return lnf;
    }

    void mian() {
        Kruscal();
        DFS(1);
        ans = lnf;
        for (int e = 2; e <= ecnt; e++) {
            int u = edge[e].tail;
            int v = edge[e].head;
            int w = edge[e].weight;
            if (edge[e].choose) continue;
            ans = std::min(ans, calc(u, v, w));
        }
        std::cout << ans << '\n';
        return;
    }
}

int main() {
    promote();
    std::cin >> N >> M;
    graph::ecnt = 1;
    for (int i = 1; i <= M; i++) {
        std::cin >> x >> y >> z;
        if (x == y) continue;
        graph::addEdge(x, y, z);
        graph::addEdge(y, x, z);
    }
    graph::mian();
    return 0;
}