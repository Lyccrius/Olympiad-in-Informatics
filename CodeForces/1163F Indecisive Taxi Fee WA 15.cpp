#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef long long lxl;
typedef std::vector<int> vic;

const int maxN = 2e5;
const int maxM = 2e5;
const int maxQ = 2e5;
const lxl inf = 1e12;

int n, m, q;
int u, v, w;
int t, x;

struct Graph {
    struct Vertex {
        int vertex;
        int head;
        int vis;
        lxl dis;
        int fa;
        int fe;
        int same;
        int onpath;

        Vertex() {
            head = -1;
            fe = -1;
            return;
        }

        bool operator<(const Vertex &other) const {
            return dis > other.dis;
        }
    } vertex[maxN + 10];

    struct Edge {
        int edge;
        int tail;
        int head;
        int next;
        int weight;
        int onpath;
        int rank;
    } edge[2 * maxM + 10];

    int ecnt;
    vic path;

    void addEdge(int tail, int head, int weight, int i) {
        edge[ecnt].edge = i;
        edge[ecnt].tail = tail;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        edge[ecnt].weight = weight;
        vertex[tail].head = ecnt;
        ecnt++;
        return;
    }

    void Dijkstra(int s, int t) {
        std::priority_queue<Vertex> q;
        for (int i = 1; i <= n; i++) vertex[i].vertex = i;
        for (int i = 1; i <= n; i++) vertex[i].vis = false;
        for (int i = 1; i <= n; i++) vertex[i].dis = inf;
        vertex[s].dis = 0;
        q.push(vertex[s]);
        while (!q.empty()) {
            int u = q.top().vertex;
            q.pop();
            if (vertex[u].vis) continue;
            vertex[u].vis = true;
            for (int e = vertex[u].head; ~e; e = edge[e].next) {
                int v = edge[e].head;
                int w = edge[e].weight;
                if (vertex[v].dis > vertex[u].dis + w) {
                    vertex[v].dis = vertex[u].dis + w;
                    vertex[v].fa = u;
                    vertex[v].fe = e;
                    q.push(vertex[v]);
                }
            }
        }
        int u = t;
        while (u != s) {
            path.push_back(edge[vertex[u].fe].edge);
            edge[vertex[u].fe].onpath = true;
            edge[vertex[u].fe ^ 1].onpath = true;
            u = vertex[u].fa;
        }
        std::reverse(path.begin(), path.end());
        for (int i = 0; i < path.size(); i++) edge[2 * path[i] - 1].rank = i + 1;
        for (int i = 0; i < path.size(); i++) edge[2 * path[i] - 2].rank = i + 1;
        std::queue<int> p;
        p.push(s);
        while (!p.empty()) {
            int u = p.front();
            p.pop();
            vertex[u].same = vertex[vertex[u].fa].same;
            if (~vertex[u].fe) if (edge[vertex[u].fe].onpath) vertex[u].same = edge[vertex[u].fe].rank;
            for (int e = vertex[u].head; ~e; e = edge[e].next) {
                int v = edge[e].head;
                if (vertex[v].fe == e) {
                    p.push(v);
                }
            }
        }
        return;
    }
} f, r;

struct SegmentTree {
    struct Node {
        lxl val;
        lxl tag;

        Node() {
            val = inf;
            tag = inf;
            return;
        }
    } node[4 * maxN + 10];

    void MakeTag(int u, lxl tag) {
        if (node[u].val <= tag) return;
        node[u].val = tag;
        node[u].tag = tag;
        return;
    }

    void PushDown(int u) {
        if (!node[u].tag) return;
        MakeTag(2 * u, node[u].tag);
        MakeTag(2 * u + 1, node[u].tag);
        node[u].tag = 0;
        return;
    }

    void PushUp(int u) {
        node[u].val = std::min(node[2 * u].val, node[2 * u + 1].val);
        return;
    }

    void Modify(int u, int l, int r, int s, int t, lxl val) {
        if (t < l) return;
        if (s > r) return;
        if (s > t) return;
        if (s <= l && r <= t) {
            MakeTag(u, val);
            return;
        }
        PushDown(u);
        int mid = (l + r) / 2;
        if (s <= mid) Modify(2 * u, l, mid, s, t, val);
        if (t >= mid + 1) Modify(2 * u + 1, mid + 1, r, s, t, val);
        PushUp(u);
        return;
    }

    lxl Query(int u, int l, int r, int pos) {
        if (pos < l) return inf;
        if (pos > r) return inf;
        if (l == r) {
            return node[u].val;
        }
        PushDown(u);
        int mid = (l + r) / 2;
        if (pos <= mid) return Query(2 * u, l, mid, pos);
        if (pos >= mid + 1) return Query(2 * u + 1, mid + 1, r, pos); 
    }
} SGT;

int main() {
    promote();
    std::cin >> n >> m >> q;
    for (int i = 1; i <= m; i++) {
        std::cin >> u >> v >> w;
        f.addEdge(u, v, w, i);
        f.addEdge(v, u, w, i);
        r.addEdge(u, v, w, i);
        r.addEdge(v, u, w, i);
    }
    f.Dijkstra(1, n);
    r.Dijkstra(n, 1);
    int tot = f.path.size();
    for (int u = 1; u <= n; u++) {
        for (int e = f.vertex[u].head; ~e; e = f.edge[e].next) {
            int v = f.edge[e].head;
            int w = f.edge[e].weight;
            if (f.edge[e].onpath) continue;
            SGT.Modify(1, 1, tot, f.vertex[u].same + 1, tot - r.vertex[v].same, f.vertex[u].dis + w + r.vertex[v].dis);
            SGT.Modify(1, 1, tot, f.vertex[v].same + 1, tot - r.vertex[u].same, f.vertex[v].dis + w + r.vertex[u].dis);
        }
    }
    for (int i = 1; i <= q; i++) {
        std::cin >> t >> x;
        t = (t - 1) * 2;
        if (f.edge[t].onpath || f.edge[t ^ 1].onpath) {
            if (!f.edge[t].onpath) t ^= 1;
            if (x >= f.edge[t].weight) {
                std::cout << std::min(f.vertex[n].dis - f.edge[t].weight + x, SGT.Query(1, 1, tot, f.edge[t].rank)) << '\n';
            } else {
                std::cout << f.vertex[n].dis - f.edge[t].weight + x << '\n';
            }
        } else {
            if (x >= f.edge[t].weight) {
                std::cout << f.vertex[n].dis << '\n';
            } else {
                int u = f.edge[t].tail;
                int v = f.edge[t].head;
                int w = f.edge[t].weight;
                std::cout << std::min(f.vertex[n].dis, std::min(f.vertex[u].dis + x + r.vertex[v].dis, f.vertex[v].dis + x + r.vertex[u].dis)) << '\n';
            }
        }
    }
    return 0;
}