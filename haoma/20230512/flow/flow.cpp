#include <iostream>

const int maxN = 1e5;
const int maxM = 2e5;
const int maxQ = 2e5;
const int inf = 1e9 + 10;

int n, m, q;
int u[maxM + 10], v[maxM + 10], w[maxM + 10];
int o[maxQ + 10], x[maxQ + 10], y[maxQ + 10];

namespace tree {
    bool is() {
        return m == n - 1;
    }
    
    struct SegmentTree {
        struct Node {
            int val;
        } node[4 * maxN + 10];

        void PushUp(int u) {
            node[u].val = std::min(node[2 * u].val, node[2 * u + 1].val);
            return;
        }

        void Modify(int u, int l, int r, int pos, int val) {
            //printf("m %d, [%d, %d]\n", u, l, r);
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
            if (s > t) return inf;
            //printf("q %d, [%d, %d], [%d, %d]\n", u, l, r, s, t);
            if (s <= l && r <= t) {
                return node[u].val;
            }
            int mid = (l + r) / 2;
            if (t <= mid) return Query(2 * u, l, mid, s, t);
            if (s >= mid + 1) return Query(2 * u + 1, mid + 1, r, s, t);
            return std::min(Query(2 * u, l, mid, s, t), Query(2 * u + 1, mid + 1, r, s, t));
        }
    } SGT;

    namespace graph {
        struct Vertex {
            int head;
            int size;
            int dep;
            int fa;
            int top;
            int dfn;
            int hson;
            int weight;
        } vertex[maxN + 10];

        struct Edge {
            int head;
            int next;
            int weight;
        } edge[2 * maxM + 10];

        int ecnt;

        void addEdge(int tail, int head, int weight) {
            ecnt++;
            edge[ecnt].head = head;
            edge[ecnt].next = vertex[tail].head;
            edge[ecnt].weight = weight;
            vertex[tail].head = ecnt;
            return;
        }

        void DFS1(int u, int from) {
            vertex[u].size = 1;
            for (int e = vertex[u].head; e; e = edge[e].next) {
                int v = edge[e].head;
                int w = edge[e].weight;
                if (v == from) continue;
                vertex[v].dep = vertex[u].dep + 1;
                vertex[v].fa = u;
                vertex[v].weight = w;
                DFS1(v, u);
                vertex[u].size += vertex[v].size;
                if (vertex[v].size > vertex[vertex[u].hson].size) {
                    vertex[u].hson = v;
                }
            }
            return;
        }

        int dfn;

        void DFS2(int u, int from, int top) {
            dfn++;
            vertex[u].dfn = dfn;
            vertex[u].top = top;
            if (vertex[u].hson) {
                DFS2(vertex[u].hson, u, top);
            }
            for (int e = vertex[u].head; e; e = edge[e].next) {
                int v = edge[e].head;
                int w = edge[e].next;
                if (v == from) continue;
                if (v == vertex[u].hson) continue;
                DFS2(v, u, v);
            }
            return;
        }

        int Query(int u, int v) {
            int ret = inf;
            //printf("query(%d, %d)\n", u, v);
            while (vertex[u].top != vertex[v].top) {
                if (vertex[vertex[u].top].dep < vertex[vertex[v].top].dep) std::swap(u, v);
                //printf("%d, %d: %d, %d\n", u, v);
                ret = std::min(ret, SGT.Query(1, 1, n, vertex[vertex[u].top].dfn + 1, vertex[u].dfn));
                u = vertex[vertex[u].top].fa;
            }
            if (vertex[u].dep > vertex[v].dep) std::swap(u, v);
                //printf("%d, %d: %d, %d\n", u, v);
            ret = std::min(ret, SGT.Query(1, 1, n, vertex[u].dfn + 1, vertex[v].dfn));
            return ret;
        }
    }

    int e[maxM + 10];

    void mian() {
        for (int i = 1; i <= m; i++) {
            graph::addEdge(u[i], v[i], w[i]);
            graph::addEdge(v[i], u[i], w[i]);
        }
        graph::vertex[1].weight = inf;
        graph::DFS1(1, 0);
        graph::DFS2(1, 0, 1);
        for (int i = 1; i <= m; i++) {
            if (graph::vertex[u[i]].dep > graph::vertex[v[i]].dep) {
                e[i] = u[i];
            } else {
                e[i] = v[i];
            }
        }
        for (int i = 1; i <= n; i++) {
            //printf("%d: %d\n", graph::vertex[i].dfn, graph::vertex[i].weight);
            SGT.Modify(1, 1, n, graph::vertex[i].dfn, graph::vertex[i].weight);
        }
        for (int i = 1; i <= q; i++) {
            if (o[i] == 0) {
                std::cout << graph::Query(x[i], y[i]) << '\n';
            } else {
                SGT.Modify(1, 1, n, graph::vertex[e[x[i]]].dfn, y[i]);
            }
        }
        return;
    }
}

namespace link {
    bool is() {
        return m == n;
    }

    int t[maxM + 10];

    namespace graph {
        struct Vertex {
            int head;
            int dfn;
            int vis;
            int weight;
        } vertex[maxN + 10];

        struct Edge {
            int head;
            int next;
            int weight;
        } edge[2 * maxM + 10];

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

        void DFS(int u, int from) {
            if (vertex[u].vis) return;
            vertex[u].vis = true;
            vertex[u].dfn = ++dfn;
            for (int e = vertex[u].head; e; e = edge[e].next) {
                int v = edge[e].head;
                int w = edge[e].weight;
                if (v == from) continue;
                vertex[v].weight = w;
                //t[(e + 1) / 2] = v;
                DFS(v, u);
            }
            return;
        }
    }

    struct SegmentTree {
        struct Node {
            int val;
        } node[4 * 2 * maxN + 10];

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
            if (s > t) return 0;
            if (s <= l && r <= t) {
                return node[u].val;
            }
            int mid = (l + r) / 2;
            if (t <= mid) return Query(2 * u, l, mid, s, t);
            if (s >= mid + 1) return Query(2 * u + 1, mid + 1, r, s, t);
            return std::min(Query(2 * u, l, mid, s, t), Query(2 * u + 1, mid + 1, r, s, t));
        }
    } SGT;

    void mian() {
        for (int i = 1; i <= m; i++) {
            graph::addEdge(u[i], v[i], w[i]);
            graph::addEdge(v[i], u[i], w[i]);
        }
        graph::DFS(1, 0);
        for (int i = 1; i <= n; i++) {
            SGT.Modify(1, 1, 2 * n, graph::vertex[i].dfn, graph::vertex[i].weight);
            SGT.Modify(1, 1, 2 * n, graph::vertex[i].dfn + n, graph::vertex[i].weight);
        }
        for (int i = 1; i <= m; i++) {
            int l = graph::vertex[u[i]].dfn;
            int r = graph::vertex[v[i]].dfn;
            if (l > r) std::swap(l, r), std::swap(u[i], v[i]);
            if (r - l == 1) t[i] = v[i];
            else t[i] = u[i];
        }
        /*
        for (int i = 1; i <= n; i++) printf("w[%d] = %d\n", i, graph::vertex[i].weight);
        for (int i = 1; i <= n; i++) printf("dfn[%d] = %d\n", i, graph::vertex[i].dfn);
        for (int i = 1; i <= m; i++) printf("e2u[%d] = %d\n", i, t[i]);
        for (int i = 1; i <= 2 * n; i++) std::cout << SGT.Query(1, 1, 2 * n, i, i) << ' '; std::cout << '\n';
        */
        for (int i = 1; i <= q; i++) {
            if (o[i] == 0) {
                if (graph::vertex[x[i]].dfn > graph::vertex[y[i]].dfn) std::swap(x[i], y[i]);
                //printf("%d + %d = ", SGT.Query(1, 1, 2 * n, graph::vertex[x[i]].dfn + 1, graph::vertex[y[i]].dfn), SGT.Query(1, 1, 2 * n, graph::vertex[y[i]].dfn + 1, graph::vertex[x[i]].dfn + n));
                std::cout << SGT.Query(1, 1, 2 * n, graph::vertex[x[i]].dfn + 1, graph::vertex[y[i]].dfn) + SGT.Query(1, 1, 2 * n, graph::vertex[y[i]].dfn + 1, graph::vertex[x[i]].dfn + n) << '\n';
            } else {
                SGT.Modify(1, 1, 2 * n, graph::vertex[t[x[i]]].dfn, y[i]);
                SGT.Modify(1, 1, 2 * n, graph::vertex[t[x[i]]].dfn + n, y[i]);
            }
        }
        return;
    }
}

int main() {
    freopen("flow.in", "r", stdin);
    freopen("flow.out", "w", stdout);
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) std::cin >> u[i] >> v[i] >> w[i];
    std::cin >> q;
    for (int i = 1; i <= q; i++) std::cin >> o[i] >> x[i] >> y[i];
    if (tree::is()) tree::mian();
    else if (link::is()) link::mian();
    return 0;
}