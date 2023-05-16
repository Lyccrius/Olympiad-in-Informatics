#include <iostream>
#include <queue>

typedef long long lxl;

const int maxN = 1e5;
const int maxM = 5e5;
const int maxK = 1e5;
const lxl inf = 1e18;

int t;
int n, m, k;
int x, y, z;
int a[maxK + 10];
lxl ans;

namespace graph {
    struct Vertex {
        int vertex;
        int head;
        int lsy;
        int vis;
        lxl dis;

        bool operator<(const Vertex &other) const {
            return dis > other.dis;
        }
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
        int weight;
    } edge[maxM + 10];

    int ecnt;

    void addEdge(int tail, int head, int weight) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        edge[ecnt].weight = weight;
        vertex[tail].head = ecnt;
        return;
    }

    void init() {
        for (int i = 1; i <= n; i++) vertex[i].vertex = i;
        for (int i = 1; i <= n; i++) vertex[i].head = -1;
        for (int i = 1; i <= n; i++) vertex[i].lsy = false;
        return;
    }

    lxl Dijkstra(int s) {
        std::priority_queue<Vertex> q;
        for (int i = 1; i <= n; i++) vertex[i].vis = false;
        for (int i = 1; i <= n; i++) vertex[i].dis = inf;
        vertex[s].dis = 0;
        q.push(vertex[s]);
        while (!q.empty()) {
            int u = q.top().vertex;
            q.pop();
            if (vertex[u].vis) continue;
            vertex[u].vis = true;
            if (vertex[u].lsy && u != s) return vertex[u].dis;
            for (int e = vertex[u].head; ~e; e = edge[e].next) {
                int v = edge[e].head;
                int w = edge[e].weight;
                if (vertex[v].dis > vertex[u].dis + w) {
                    vertex[v].dis = vertex[u].dis + w;
                    q.push(vertex[v]);
                }
            }
        }
        return inf;
    }
}

void mian() {
    std::cin >> n >> m >> k;
    graph::init();
    ans = inf;
    for (int i = 1; i <= m; i++) {
        std::cin >> x >> y >> z;
        graph::addEdge(x, y, z);
    }
    for (int i = 1; i <= k; i++) {
        std::cin >> a[i];
        graph::vertex[a[i]].lsy = true;
    }
    for (int i = 1; i <= k; i++) ans = std::min(ans, graph::Dijkstra(a[i]));
    std::cout << ans << '\n';
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}