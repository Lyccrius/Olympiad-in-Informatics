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

struct Graph {
    struct Vertex {
        int vertex;
        int head;
        int lsy;
        int vis;
        lxl dis;
        int fa;

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

    void Dijkstra() {
        std::priority_queue<Vertex> q;
        for (int i = 1; i <= n; i++) vertex[i].vis = false;
        for (int i = 1; i <= n; i++) vertex[i].dis = inf;
        for (int i = 1; i <= k; i++) vertex[a[i]].dis = 0;
        for (int i = 1; i <= k; i++) vertex[a[i]].fa = i;
        for (int i = 1; i <= k; i++) q.push(vertex[a[i]]);
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
                    vertex[v].fa = vertex[u].fa;
                    q.push(vertex[v]);
                }
            }
        }
        return;
    }
} forward, reverse;

void mian() {
    std::cin >> n >> m >> k;
    forward.init();
    reverse.init();
    ans = inf;
    for (int i = 1; i <= m; i++) {
        std::cin >> x >> y >> z;
        forward.addEdge(x, y, z);
        reverse.addEdge(y, x, z);
    }
    for (int i = 1; i <= k; i++) {
        std::cin >> a[i];
        forward.vertex[a[i]].lsy = true;
        reverse.vertex[a[i]].lsy = true;
    }
    forward.Dijkstra();
    reverse.Dijkstra();
    for (int u = 1; u <= n; u++) {
        for (int e = forward.vertex[u].head; ~e; e = forward.edge[e].next) {
            int v = forward.edge[e].head;
            int w = forward.edge[e].weight;
            if (forward.vertex[u].fa == reverse.vertex[v].fa) continue;
            ans = std::min(ans, forward.vertex[u].dis + w + reverse.vertex[v].dis);
        }
    }
    std::cout << ans << '\n';
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}