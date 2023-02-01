#include <iostream>
#include <vector>

typedef long long lxl;

const int maxN = 1e5;
const int maxM = 2e5;
const int mod = 1e9 + 7;

int n, m;
int a[maxN + 10];
int u[maxM + 10], v[maxM + 10];
int w = 1;
int tot[2];
lxl ans;

namespace tree {
    struct Vertex {
        int head;
        int size[2];
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
        int weight;
    } edge[maxN * 2 + 10];

    int ecnt;

    void addEdge(int tail, int head, int weight) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].weight = weight;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    void DFS(int u, int from) {
        vertex[u].size[a[u]]++;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            int w = edge[e].weight;
            if (v == from) continue;
            DFS(v, u);
            vertex[u].size[0] += vertex[v].size[0];
            vertex[u].size[1] += vertex[v].size[1];
        }
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            int w = edge[e].weight;
            if (v == from) continue;
            ans = (ans + 1ll * vertex[v].size[0] * (tot[1] - vertex[v].size[1]) % mod * w) % mod;
            ans = (ans + 1ll * vertex[v].size[1] * (tot[0] - vertex[v].size[0]) % mod * w) % mod;
        }
        return;
    }
}

namespace graph {
    struct Vertex {
        int fa;
    } vertex[maxN + 10];

    struct Edge {
        int tail;
        int head;
        int weight;
    };

    std::vector<Edge> edge;

    void addEdge(int tail, int head, int weight) {
        edge.push_back((Edge) {tail, head, weight});
        return;
    }

    struct DisjointSetUnion {
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

        void Init() {
            for (int u = 1; u <= n; u++) vertex[u].fa = u;
            return;
        }
    } DSU;

    void Kruscal() {
        DSU.Init();
        for (int e = 0; e < edge.size(); e++) {
            int u = edge[e].tail;
            int v = edge[e].head;
            int w = edge[e].weight;
            int fu = DSU.Find(u);
            int fv = DSU.Find(v);
            if (fu == fv) continue;
            DSU.Union(u, v);
            tree::addEdge(u, v, w);
            tree::addEdge(v, u, w);
        }
        return;
    }
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) std::cin >> a[i], tot[a[i]]++;
    for (int i = 1; i <= m; i++) std::cin >> u[i] >> v[i], w = w * 2 % mod, graph::addEdge(u[i], v[i], w);
    graph::Kruscal();
    tree::DFS(1, 0);
    std::cout << ans;
    return 0;
}