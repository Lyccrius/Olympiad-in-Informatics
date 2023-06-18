#include <iostream>
#include <vector>

typedef std::vector<int> vic;

const int maxN = 1e5;
const int maxM = 1e5;

int t;
int n, m;
int a, b;
int x, k;
int day[maxM + 10];
int ans[maxM + 10];

namespace graph {
    struct Vertex {
        int head;
        int part;
        int size;
        int vis;
        int dis;
        vic q;
    } vertex[maxN + 10], e;

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

    int root;
    int tot;

    void calcSize(int u, int from) {
        vertex[u].part = 0;
        vertex[u].size = 1;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            if (vertex[v].vis) continue;
            calcSize(v, u);
            vertex[u].part = std::max(vertex[u].part, vertex[v].size);
            vertex[u].size += vertex[v].size;
        }
        vertex[u].part = std::max(vertex[u].part, tot - vertex[u].size);
        if (vertex[root].part > vertex[u].part) root = u;
        return;
    }

    vic sub;
    vic vis;
    int res[maxN + 10];

    void calcDist(int u, int from) {
        sub.push_back(u);
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            if (vertex[v].vis) continue;
            vertex[v].dis = vertex[u].dis + 1;
            calcDist(v, u);
        }
        return;
    }

    void divide(int u) {
        res[0]++;
        vis.push_back(0);
        vertex[u].vis = true;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (vertex[v].vis) continue;
            vertex[v].dis = 1;
            calcDist(v, u);
            for (auto i : sub) {
                res[vertex[i].dis]++;
                vis.push_back(vertex[i].dis);
            }
            sub.clear();
        }
        for (auto j : vertex[u].q) {
            ans[j] += res[day[j]];
            //printf("%d: %d\n", j, res[day[j]]);
        }
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (vertex[v].vis) continue;
            vertex[v].dis = 1;
            calcDist(v, u);
            for (auto i : sub) {
                res[vertex[i].dis]--;
            }
            for (auto i : sub) {
                for (auto j : vertex[i].q) {
                    if (day[j] >= vertex[i].dis) {
                        ans[j] += res[day[j] - vertex[i].dis];
                    }
                }
            }
            for (auto i : sub) {
                res[vertex[i].dis]++;
            }
            sub.clear();
        }
        for (auto i : vis) res[i] = 0;
        vis.clear();
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (vertex[v].vis) continue;
            tot = vertex[v].size;
            root = 0;
            vertex[root].part = maxN;
            calcSize(v, u);
            calcSize(root, u);
            divide(root);
        }
        return;
    }

    void clear() {
        for (int i = 1; i <= n; i++) vertex[i] = e;
        for (int i = 1; i <= m; i++) ans[i] = 0;
        ecnt = 0;
        return;
    }
}

void mian() {
    graph::clear();
    std::cin >> n >> m;
    for (int i = 1; i < n; i++) std::cin >> a >> b, graph::addEdge(a, b), graph::addEdge(b, a);
    for (int i = 1; i <= m; i++) std::cin >> x >> k, graph::vertex[x].q.push_back(i), day[i] = k;
    graph::root = 0;
    graph::tot = n;
    graph::vertex[graph::root].part = maxN;
    graph::calcSize(1, 0);
    graph::calcSize(graph::root, 0);
    graph::divide(graph::root);
    for (int i = 1; i <= m; i++) std::cout << ans[i] << '\n';
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}