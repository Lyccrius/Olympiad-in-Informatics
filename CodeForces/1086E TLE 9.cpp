#include <iostream>
#include <deque>

typedef long long lxl;

const int maxN = 1e5;
const int maxQ = 1e5;

int n, q;
int a[maxN + 10];
int p[maxN + 10];
int x, y;

struct Query {
    int id;
    int other;
    lxl res;
};

lxl ans[maxQ + 10];

namespace graph {
    struct Vertex {
        int head;
        lxl res;
        int fa;
        std::deque<Query> q;
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
    } edge[maxN * 2 + 10];

    int ecnt;

    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    void DFS(int u, int from) {
        vertex[u].res = vertex[from].res + 1ll * a[u] * a[u];
        vertex[u].fa = from;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            DFS(v, u);
        }
        return;
    }

    void DFS2(int u, int from) {
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            DFS2(v, u);
        }
        while (vertex[u].q.size()) {
            Query query = vertex[u].q.front(); vertex[u].q.pop_front();
            if (u == query.other) {
                ans[query.id] = query.res + vertex[u].res;
            } else {
                vertex[from].q.push_back((Query) {query.id, vertex[query.other].fa, query.res + 1ll * a[u] * a[query.other]});
            }
        }
        vertex[u].q.resize(0);
        return;
    }

    void solve(int u, int v) {
        lxl ans = 0;
        while (u != v) {
            ans += 1ll * a[u] * a[v];
            u = vertex[u].fa;
            v = vertex[v].fa;
        }
        ans += vertex[u].res;
        std::cout << ans << '\n';
        return;
    }
}

int main() {
    std::cin >> n >> q;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 2; i <= n; i++) std::cin >> p[i];
    for (int i = 2; i <= n; i++) graph::addEdge(i, p[i]);
    for (int i = 2; i <= n; i++) graph::addEdge(p[i], i);
    graph::DFS(1, 0);
    for (int i = 1; i <= q; i++) {
        std::cin >> x >> y;
        graph::vertex[x].q.push_back((Query) {i, y, 0});
    }
    graph::DFS2(1, 0);
    for (int i = 1; i <= q; i++) {
        std::cout << ans[i] << '\n';
    }
    return 0;
}