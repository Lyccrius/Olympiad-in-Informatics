#include <iostream>
#include <vector>

typedef std::vector<int> vic;

const int maxN = 1e4;
const int maxM = 100;
const int maxK = 1e7;
const int maxW = 1e4;

int n, m;
int u, v, w;
int a[maxM + 10];
int ans[maxM + 10];

namespace graph {
    struct Vertex {
        int head;
        int part;
        int size;
        int vis;
        int dis;
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

    int root;
    int tot;
    vic q;
    vic t;
    bool res[maxK + 10];

    void calcSize(int u, int from) {
        vertex[u].part = 0;
        vertex[u].size = 1;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            int w = edge[e].weight;
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

    void calcDist(int u, int from) {
        t.push_back(vertex[u].dis);
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            int w = edge[e].weight;
            if (v == from) continue;
            if (vertex[v].vis) continue;
            vertex[v].dis = vertex[u].dis + w;
            calcDist(v, u);
        }
        return;
    }

    void divide(int u, int from) {
        res[0] = true;
        q.push_back(0);
        vertex[u].vis = true;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            int w = edge[e].weight;
            if (v == from) continue;
            if (vertex[v].vis) continue;
            vertex[v].dis = w;
            calcDist(v, u);
            for (auto i : t) {
                for (int j = 1; j <= m; j++) {
                    if (a[j] >= i) {
                        ans[j] |= res[a[j] - i];
                    }
                }
            }
            for (auto i : t) {
                if (i <= maxK) {
                    q.push_back(i);
                    res[i] = true;
                }
            }
            t.clear();
        }
        for (auto i : q) res[i] = false;
        q.clear();
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            int w = edge[e].weight;
            if (v == from) continue;
            if (vertex[v].vis) continue;
            tot = vertex[v].size;
            root = 0;
            vertex[root].part = maxN;
            calcSize(v, u);
            calcSize(root, 0);
            divide(root, u);
        }
        return;
    }
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n - 1; i++) std::cin >> u >> v >> w, graph::addEdge(u, v, w), graph::addEdge(v, u, w);
    for (int i = 1; i <= m; i++) std::cin >> a[i];
    graph::root = 0;
    graph::tot = n;
    graph::vertex[graph::root].part = maxN;
    graph::calcSize(1, 0);
    graph::calcSize(graph::root, 0);
    graph::divide(graph::root, 0);
    for (int i = 1; i <= m; i++) if (ans[i]) std::cout << "AYE" << '\n'; else std::cout << "NAY" << '\n';
    return 0;
}