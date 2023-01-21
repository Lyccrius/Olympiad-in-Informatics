#include <iostream>
#include <algorithm>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef long long lxl;

const int maxN = 2e5;
const int maxC = 1e6;

int N, K;
int a, b, c;
int t;
lxl sum;

namespace graph {
    struct Vertex {
        int vis;
        int di;
        int fa;
    } vertex[maxN + 10];

    struct Edge {
        int tail;
        int head;
        int weight;

        bool operator<(const Edge &other) const {
            return weight < other.weight;
        }
    } edge[maxN];

    int ecnt;

    void addEdge(int tail, int head, int weight) {
        ecnt++;
        edge[ecnt].tail = tail;
        edge[ecnt].head = head;
        edge[ecnt].weight = weight;
        return;
    }

    struct DisjointSetUnion {
        int Find(int u) {
            if (vertex[u].fa == u) return u;
            return vertex[u].fa = Find(vertex[u].fa);
        }

        void Union(int u, int v) {
            vertex[u].di |= vertex[v].di;
            vertex[v].di |= vertex[u].di;
            vertex[u].fa = v;
            return;
        }
    } DSU;

    lxl Kruscal() {
        lxl ret = 0;
        std::sort(edge + 1, edge + ecnt + 1);
        for (int i = 1; i <= N; i++) vertex[i].fa = i;
        for (int i = 1; i <= ecnt; i++) {
            int u = edge[i].tail;
            int v = edge[i].head;
            int w = edge[i].weight;
            u = DSU.Find(u);
            v = DSU.Find(v);
            if (vertex[u].di && vertex[v].di) continue;
            DSU.Union(u, v);
            vertex[v].di = vertex[u].di || vertex[v].di;
            ret += w;
        }
        return ret;
    }
}

int main() {
    std::cin >> N >> K;
    for (int i = 1; i <= K; i++) std::cin >> t, graph::vertex[t].di = true;
    for (int i = 1; i < N; i++) std::cin >> a >> b >> c, graph::addEdge(a, b, -c), sum += c;
    std::cout << sum + graph::Kruscal();
    return 0;
}