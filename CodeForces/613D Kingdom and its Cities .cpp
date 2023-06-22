#include <iostream>
#include <algorithm>
#include <vector>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef std::vector<int> vic;

const int maxN = 1e5;
const int maxQ = 1e5;
const int maxK = 1e5;

int n;
int u, v;
int q;
int k;
int a[maxK + 10];
int b[2 * maxK + 10];
int m;
int ans;
vic vis;

namespace graph {
    struct Vertex {
        int mark;
        int head;
        int hson;
        int size;
        int dep;
        int dfn;
        int top;
        int fa;
        int f;
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
    } edge[2 * maxN + 10];

    int ecnt;

    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    void DFS0(int u, int from) {
        vertex[u].size = 1;
        vertex[u].dep = vertex[from].dep + 1;
        vertex[u].fa = from;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            DFS0(v, u);
            vertex[u].size += vertex[v].size;
            if (vertex[v].size > vertex[vertex[u].hson].size) vertex[u].hson = v;
        }
        return;
    }

    int dfn;

    void DFS1(int u, int from, int top) {
        dfn++;
        vertex[u].dfn = dfn;
        vertex[u].top = top;
        if (vertex[u].hson) DFS1(vertex[u].hson, u, top);
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            if (v == vertex[u].hson) continue;
            DFS1(v, u, v);
        }
        return;
    }

    int LCA(int u, int v) {
        while (vertex[u].top != vertex[v].top) {
            if (vertex[vertex[u].top].dep < vertex[vertex[v].top].dep) std::swap(u, v);
            u = vertex[vertex[u].top].fa;
        }
        if (vertex[u].dep > vertex[v].dep) std::swap(u, v);
        return u;
    }

    namespace virtualTree {
        Vertex vertex[maxN + 10];
        Edge edge[2 * maxN + 10];
        int ecnt;

        void addEdge(int tail, int head) {
            ecnt++;
            edge[ecnt].head = head;
            edge[ecnt].next = vertex[tail].head;
            vertex[tail].head = ecnt;
            return;
        }

        bool cmp(int u, int v) {
            return graph::vertex[u].dfn < graph::vertex[v].dfn;
        }

        void build() {
            for (int i = 1; i <= k; i++) vertex[a[i]].mark = true;
            std::sort(a + 1, a + k + 1, cmp);
            for (int i = 1; i < k; i++) {
                b[++m] = a[i];
                b[++m] = LCA(a[i], a[i + 1]);
            }
            b[++m] = a[k];
            std::sort(b + 1, b + m + 1, cmp);
            m = std::unique(b + 1, b + m + 1) - b - 1;
            for (int i = 1; i <= m; i++) vis.push_back(b[i]);
            for (int i = 1; i < m; i++) {
                int lca = LCA(b[i], b[i + 1]);
                vis.push_back(lca);
                addEdge(lca, b[i + 1]);
                addEdge(b[i + 1], lca);
            }
            return;
        }

        void clear() {
            for (int i = 1; i <= k; i++) vertex[a[i]].mark = false;
            for (auto i : vis) {
                vertex[i].head = 0;
                vertex[i].f = 0;
            }
            ecnt = 0;
            m = 0;
            ans = 0;
            vis.clear();
            return;
        }

        void DFS(int u, int from) {
            int cnt = 0;
            for (int e = vertex[u].head; e; e = edge[e].next) {
                int v = edge[e].head;
                if (v == from) continue;
                DFS(v, u);
                cnt += vertex[v].f;
            }
            if (vertex[u].mark) {
                vertex[u].f = true;
                ans += cnt;
            } else {
                if (cnt > 1) ans++;
                if (cnt == 1)  vertex[u].f = true;
            }
            return;
        }

        void solve() {
            for (int i = 1; i <= k; i++) {
                if (vertex[graph::vertex[a[i]].fa].mark) {
                    std::cout << -1 << '\n';
                    return;
                }
            }
            DFS(b[1], 0);
            std::cout << ans << '\n';
            return;
        }
    }
}

int main() {
    promote();
    std::cin >> n;
    for (int i = 1; i <= n - 1; i++) std::cin >> u >> v, graph::addEdge(u, v), graph::addEdge(v, u);
    graph::DFS0(1, 0);
    graph::DFS1(1, 0, 1);
    std::cin >> q;
    for (int i = 1; i <= q; i++) {
        std::cin >> k;
        for (int j = 1; j <= k; j++) std::cin >> a[j];
        graph::virtualTree::build();
        graph::virtualTree::solve();
        graph::virtualTree::clear();
    }
    return 0;
}