#include <iostream>
#include <algorithm>
#include <vector>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 5e5;
const int maxM = 5e5;
const int maxQ = 5e5;

int n, m;
int u, v, w;
int q;
int k, e;

namespace graph {
    struct Edge {
        int tail;
        int head;
        int weight;

        bool operator<(const Edge &other) const {
            return weight < other.weight;
        }
    };

    std::vector<Edge> edges;

    void addEdge(int tail, int head, int weight) {
        edges.push_back((Edge) {tail, head, weight});
        return;
    }

    struct DisjointSetUnion {
        struct Node {
            int fa;
            int height;
        } node[maxN + 10];

        std::vector<Node> files;

        void Init() {
            for (int i = 1; i <= n; i++) {
                node[i].fa = i;
                node[i].height = 1;
            }
            return;
        }

        int Find(int u) {
            if (node[u].fa == u) return u;
            return Find(node[u].fa);
        }

        void BackUp(int u) {
            files.push_back(node[u]);
            return;
        }

        void Restore() {
            int u = files.back().fa;
            int h = files.back().height;
            files.pop_back();
            node[u].fa = u;
            node[u].height = h;
            return;
        }

        void Union(int u, int v, int type) {
            u = Find(u);
            v = Find(v);
            if (u == v) return;
            if (node[u].height > node[v].height) std::swap(u, v);
            if (type) BackUp(u);
            node[u].fa = v;
            node[v].height = std::max(node[v].height, node[u].height + 1);
            return;
        }

        void RollBack() {
            while (files.size()) Restore();
            return;
        }
    } DSU;
}

struct Query {
    int i;
    int e;

    bool operator<(const Query &other) const {
        if (graph::edges[e].weight != graph::edges[other.e].weight) {
            return graph::edges[e].weight < graph::edges[other.e]. weight;
        }
        return i < other.i;
    }
};

std::vector<graph::Edge> edges;
std::vector<Query> querys;

void addEdge(int tail, int head, int weight) {
    edges.push_back((graph::Edge) {tail, head, weight});
    return;
}

void addQuery(int i, int e) {
    querys.push_back((Query) {i, e - 1});
    return;
}

bool ans[maxQ + 10];

int main() {
    promote();
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        std::cin >> u >> v >> w;
        addEdge(u, v, w);
        graph::addEdge(u, v, w);
    }
    std::cin >> q;
    for (int i = 1; i <= q; i++) {
        std::cin >> k;
        for (int j = 1; j <= k; j++) {
            std::cin >> e;
            addQuery(i, e);
        }
        ans[i] = true;
    }
    std::sort(edges.begin(), edges.end());
    std::sort(querys.begin(), querys.end());
    graph::DSU.Init();
    int e = 0;
    for (int i = 0; i < querys.size(); i++) {
        Query query = querys[i];
        if (!ans[query.i]) continue;
        if (i) {
            if (querys[i - 1].i < querys[i].i ||
                graph::edges[querys[i - 1].e].weight < graph::edges[querys[i].e].weight) {
                graph::DSU.RollBack();
            }
        }
        while (e < edges.size() && edges[e].weight < graph::edges[query.e].weight) {
            graph::DSU.Union(edges[e].head, edges[e].tail, 0);
            e++;
        } 
        if (graph::DSU.Find(graph::edges[query.e].tail) != graph::DSU.Find(graph::edges[query.e].head)) {
            graph::DSU.Union(graph::edges[query.e].tail, graph::edges[query.e].head, 1);
        } else {
            ans[query.i] = false;
        }
    }
    for (int i = 1; i <= q; i++) {
        if (ans[i]) {
            std::cout << "YES" << '\n';
        } else {
            std::cout << "NO" << '\n';
        }
    }
    return 0;
}