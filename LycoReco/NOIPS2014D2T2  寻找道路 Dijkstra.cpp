#include <iostream>
#include <queue>

const int maxN = 1e4;
const int maxM = 2e5;
const int inf = 1e9;

int n, m;
int x, y;
int s, t;

struct Graph {
    struct Vertex {
        int vertex;
        int head;
        int vis;
        int dis;
        int ok;

        bool operator<(const Vertex &other) const {
            return dis > other.dis;
        }
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
    } edge[maxM + 10];

    int ecnt;

    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    void Dijkstra(int s) {
        std::priority_queue<Vertex> q;
        for (int u = 1; u <= n; u++) vertex[u].vertex = u;
        for (int u = 1; u <= n; u++) vertex[u].dis = inf;
        vertex[s].dis = 0;
        q.push(vertex[s]);
        while (!q.empty()) {
            int u = q.top().vertex;
            q.pop();
            if (vertex[u].vis) continue;
            vertex[u].vis = true;
            for (int e = vertex[u].head; e; e = edge[e].next) {
                int v = edge[e].head;
                if (!vertex[v].ok) continue;
                if (vertex[v].dis > vertex[u].dis + 1) {
                    vertex[v].dis = vertex[u].dis + 1;
                    q.push(vertex[v]);
                }
            }
        }
        return;
    }
} G, R;

void BFS(int u) {
    std::queue<int> q;
    q.push(t);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (R.vertex[u].vis) continue;
        R.vertex[u].vis = true;
        for (int e = R.vertex[u].head; e; e = R.edge[e].next) {
            int v = R.edge[e].head;
            q.push(v);
        }
    }
    for (int u = 1; u <= n; u++) if (R.vertex[u].vis) G.vertex[u].ok = true;
    for (int u = 1; u <= n; u++) {
        if (R.vertex[u].vis) continue;
        for (int e = R.vertex[u].head; e; e = R.edge[e].next) {
            int v = R.edge[e].head;
            G.vertex[v].ok = false;
        }
    }
    return;
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        std::cin >> x >> y;
        G.addEdge(x, y);
        R.addEdge(y, x);
    }
    std::cin >> s >> t;
    BFS(t);
    G.Dijkstra(s);
    if (G.vertex[t].dis == inf) G.vertex[t].dis = -1;
    std::cout << G.vertex[t].dis;
    return 0;
}