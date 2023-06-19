#include <iostream>
#include <algorithm>
#include <vector>

typedef std::vector<int> vic;

#define int long long

const int maxN = 2.5e5;
const int maxM = 5e5;
const int sumK = 5e5;
const int maxW = 1e5;

int n;
int u, v, w;
int m;
int k;
int h[sumK + 10];
int a[2 * sumK + 10];
int t;
vic vis;

struct SegmentTree {
    struct Node {
        int val;
    } node[4 * maxN + 10];

    void PushUp(int u) {
        node[u].val = std::min(node[2 * u].val, node[2 * u + 1].val);
        return;
    }

    void Modify(int u, int l, int r, int pos, int val) {
        if (l == r) {
            node[u].val = val;
            return;
        }
        int mid = (l + r) / 2;
        if (pos <= mid) Modify(2 * u, l, mid, pos, val);
        if (pos >= mid + 1) Modify(2 * u + 1, mid + 1, r, pos, val);
        PushUp(u);
        return;
    }

    int Query(int u, int l, int r, int s, int t) {
        //printf("query(%d, [%d, %d], [%d, %d])\n", u, l, r, s, t);
        if (s > t) return maxW;
        if (s <= l && r <= t) return node[u].val;
        int mid = (l + r) / 2;
        if (t <= mid) return Query(2 * u, l, mid, s, t);
        if (s >= mid + 1) return Query(2 * u + 1, mid + 1, r, s, t);
        return std::min(Query(2 * u, l, mid, s, t), Query(2 * u + 1, mid + 1, r, s, t));
    }
} SGT;

namespace graph {
    struct Vertex {
        int head;
        int hson;
        int size;
        int top;
        int key;
        int dfn;
        int dep;
        int fa;
        long long f;
        int w;
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
        int weight;
    } edge[2 * maxN + 10];

    int ecnt;

    void addEdge(int tail, int head, int weight) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        edge[ecnt].weight = weight;
        vertex[tail].head = ecnt;
        return;
    }

    int dfn;

    void DFS0(int u, int from) {
        vertex[u].size = 1;
        //printf("vertex[%d].min = %d\n", u, vertex[u].min);
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            int w = edge[e].weight;
            if (v == from) continue;
            vertex[v].dep = vertex[u].dep + 1;
            vertex[v].fa = u;
            vertex[v].w = w;
            DFS0(v, u);
            vertex[u].size += vertex[v].size;
            if (vertex[v].size > vertex[vertex[u].hson].size) vertex[u].hson = v;
        }
        return;
    }

    void DFS1(int u, int from, int top) {
        dfn++;
        vertex[u].dfn = dfn;
        vertex[u].top = top;
        SGT.Modify(1, 1, n, vertex[u].dfn, vertex[u].w);
        if (vertex[u].hson) DFS1(vertex[u].hson, u, top);
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            if (v == vertex[u].hson) continue;
            DFS1(v, u, v);
        }
        return;
    }

    bool cmp(int u, int v) {
        return vertex[u].dfn < vertex[v].dfn;
    }

    int LCA(int u, int v) {
        //printf("LCA(%d, %d) = ", u, v);
        while (vertex[u].top != vertex[v].top) {
            if (vertex[vertex[u].top].dep < vertex[vertex[v].top].dep) std::swap(u, v);
            u = vertex[vertex[u].top].fa;
        }
        if (vertex[u].dep > vertex[v].dep) std::swap(u, v);
        //printf("%d\n", u);
        return u;
    }

    int DIS(int u, int v) {
        int ret = maxW;
        while (vertex[u].top != vertex[v].top) {
            if (vertex[vertex[u].top].dep < vertex[vertex[v].top].dep) std::swap(u, v);
            //printf("top[%d] = %d\n", u, vertex[u].top);
            //printf("top[%d] = %d\n", v, vertex[v].top);
            ret = std::min(ret, SGT.Query(1, 1, n, vertex[vertex[u].top].dfn, vertex[u].dfn));
            //printf("%d to %d = %d\n", vertex[vertex[u].top].fa, u, SGT.Query(1, 1, n, vertex[vertex[u].top].dfn, vertex[u].dfn));
            u = vertex[vertex[u].top].fa;
            //printf("u = %d\n", u);
        }
        if (vertex[u].dep > vertex[v].dep) std::swap(u, v);
        //printf("%d to %d = %d\n", u, v, SGT.Query(1, 1, n, vertex[u].dfn + 1, vertex[v].dfn));
        ret = std::min(ret, SGT.Query(1, 1, n, vertex[u].dfn + 1, vertex[v].dfn));
        //printf("ret = %d\n", ret);
        return ret;
    }

    namespace virtualTree {
        Vertex vertex[maxN + 10];
        Edge edge[2 * maxN + 10];
        int ecnt;

        void addEdge(int tail, int head, int weight) {
            //printf("v::add(%d, %d, %d)\n", tail, head, weight);
            ecnt++;
            edge[ecnt].head = head;
            edge[ecnt].next = vertex[tail].head;
            edge[ecnt].weight = weight;
            vertex[tail].head = ecnt;
            return;
        }

        void build() {
            std::sort(h + 1, h + k + 1, cmp);
            for (int i = 1; i < k; i++) {
                a[++t] = h[i];
                a[++t] = LCA(h[i], h[i + 1]);
            }
            a[++t] = 1;
            a[++t] = h[k];
            std::sort(a + 1, a + t + 1, cmp);
            t = std::unique(a + 1, a + t + 1) - a - 1;
            for (int i = 1; i < t; i++) {
                //printf("[%d] %d, [%d], %d\n", i, a[i], i + 1, a[i + 1]);
                int lca = LCA(a[i], a[i + 1]);
                int dis = DIS(lca, a[i + 1]);
                addEdge(lca, a[i + 1], dis);
                vis.push_back(lca);
                vis.push_back(a[i + 1]);
                //addEdge(lca, a[i + 1], graph::vertex[a[i + 1]].dep - graph::vertex[lca].dep);
                //addEdge(a[i + 1], lca, graph::vertex[a[i + 1]].dep - graph::vertex[lca].dep);
            }
            for (int i = 1; i <= k; i++) vertex[h[i]].key = true;
            return;
        }  

        void clear() {
            for (int i = 1; i <= k; i++) vertex[h[i]].key = false;
            for (auto i : vis) {
                vertex[i].f = 0;
                vertex[i].head = 0;
            }
            t = 0;
            ecnt = 0;
            vis.clear();
            return;
        }

        void dp(int u, int from) {
            for (int e = vertex[u].head; e; e = edge[e].next) {
                int v = edge[e].head;
                int w = edge[e].weight;
                if (v == from) continue;
                dp(v, u);
                if (vertex[v].key) {
                    vertex[u].f += w;
                } else {
                    vertex[u].f += std::min(vertex[v].f, w);
                }
            }
            if (vertex[u].key) vertex[u].f = maxW;
            return;
        }
    }
}

signed main() {
    std::cin >> n;
    for (int i = 1; i <= n - 1; i++) std::cin >> u >> v >> w, graph::addEdge(u, v, w), graph::addEdge(v, u, w);
    graph::DFS0(1, 0);
    graph::DFS1(1, 0, 1);
    std::cin >> m;
    for (int i = 1; i <= m; i++) {
        std::cin >> k;
        for (int j = 1; j <= k; j++) std::cin >> h[j];
        graph::virtualTree::clear();
        graph::virtualTree::build();
        graph::virtualTree::dp(1, 0);
        std::cout << graph::virtualTree::vertex[1].f << '\n';
    }
    return 0;
}