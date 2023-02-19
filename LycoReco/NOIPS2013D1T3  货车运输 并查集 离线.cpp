#include <iostream>
#include <algorithm>
#include <vector>

const int maxN = 1e4;
const int maxM = 5e4;
const int maxQ = 3e4;
const int maxZ = 1e5;

int n, m;
int x, y, z;
int q;

struct Query {
    int other;
    int id;
};

int ans[maxQ + 10];

namespace graph {
    struct Vertex {
        int dep;
        int head;
        int weight;
        std::vector<Query> query;
    } vertex[maxN + 10];

    struct Edge {
        int tail;
        int head;
        int weight;

        bool operator<(const Edge &other) const {
            return weight > other.weight;
        }
    };

    std::vector<Edge> edges;

    struct DisjointSetUnion {
        struct Node {
            int fa;
        } node[maxN + 10];

        void Init() {
            for (int u = 1; u <= n; u++) node[u].fa = u;
            return;
        }

        int Find(int u) {
            if (node[u].fa == u) return u;
            return node[u].fa = Find(node[u].fa);
        }

        void Union(int u, int v) {
            int fu = Find(u);
            int fv = Find(v);
            if (fu == fv) return;
            node[fu].fa = fv;
            return;
        }
    } DSU;

    void Kruscal() {
        DSU.Init();
        std::sort(edges.begin(), edges.end());
        for (auto e : edges) {
            int u = e.tail;
            int v = e.head;
            int w = e.weight;
            int fu = DSU.Find(u);
            int fv = DSU.Find(v);
            if (fu == fv) continue;
            DSU.Union(fu, fv);
            for (auto q : vertex[fu].query) {
                if (ans[q.id] != - 1) continue;
                int t = q.other;
                int ft = DSU.Find(t);
                if (ft == fv) ans[q.id] = w;
                else vertex[fv].query.push_back(q);
            }
        }
        return;
    }
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        std::cin >> x >> y >> z;
        graph::edges.push_back((graph::Edge) {x, y, z});
    }
    std::cin >> q;
    for (int i = 1; i <= q; i++) {
        std::cin >> x >> y;
        graph::vertex[x].query.push_back((Query) {y, i});
        graph::vertex[y].query.push_back((Query) {x, i});
        ans[i] = - 1;
    }
    graph::Kruscal();
    for (int i = 1; i <= q; i++) std::cout << ans[i] << '\n';
    return 0;
}