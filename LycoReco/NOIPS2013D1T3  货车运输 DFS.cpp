#include <iostream>
#include <algorithm>
#include <vector>

const int maxN = 1e4;
const int maxM = 5e4;
const int maxQ = 3e4;
const int maxZ = 1e5;
const int logZ = 17;

int n, m;
int x, y, z;
int q;

struct Query {
    int id;
    int s, t;
} query[maxQ + 10];
int ans[maxQ + 10];

typedef std::vector<Query> veq;

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

    bool check(int u, int v) {
        int fu = DSU.Find(u);
        int fv = DSU.Find(v);
        return fu == fv;
    }

    void solve(int l, int r, veq querys) {
        int mid = (l + r + 1) / 2;
        veq queryl;
        veq queryr;
        DSU.Init();
        for (auto edge : edges) {
            if (edge.weight >= mid) {
                DSU.Union(edge.tail, edge.head);
            } else break;
        }
        for (auto query : querys) {
            if (check(query.s, query.t)) queryr.push_back(query);
            else queryl.push_back(query);
        }
        if (l == r) {
            for (auto query : queryl) ans[query.id] = - 1;
            for (auto query : queryr) ans[query.id] = l;
            return;
        }
        if (queryr.size()) solve(mid, r, queryr);
        if (queryl.size()) solve(l, mid - 1, queryl);
        return;
    }
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        std::cin >> x >> y >> z;
        graph::edges.push_back((graph::Edge) {x, y, z});
    }
    std::sort(graph::edges.begin(), graph::edges.end());
    std::cin >> q;
    veq querys;
    for (int i = 1; i <= q; i++) {
        std::cin >> x >> y;
        query[i] = (Query) {i, x, y};
        querys.push_back(query[i]);
    }
    graph::solve(1, maxZ, querys);
    for (int i = 1; i <= q; i++) std::cout << ans[i] << '\n';
    return 0;
}