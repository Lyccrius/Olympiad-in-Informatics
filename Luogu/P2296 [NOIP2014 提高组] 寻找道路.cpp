#include <iostream>
#include <queue>

const int maxN = 1e4;
const int maxM = 2e5;
const int inf = 1e9 + 10;

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
} G, R;

void BFS() {
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
    q.push(t);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (G.vertex[u].vis) continue;
        G.vertex[u].vis = true;
        G.vertex[u].ok = true;
        for (int e = G.vertex[u].head; e; e = G.edge[e].next) {
            int v = G.edge[e].head;
            if (!R.vertex[v].vis) G.vertex[u].ok = false;
        }
        for (int e = R.vertex[u].head; e; e = R.edge[e].next) {
            int v = R.edge[e].head;
            q.push(v);
        }
    }
    for (int u = 1; u <= n; u++) G.vertex[u].vis = false;
    for (int u = 1; u <= n; u++) G.vertex[u].dis = inf;
    G.vertex[s].dis = 0;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (G.vertex[u].vis) continue;
        G.vertex[u].vis = true;
        for (int e = G.vertex[u].head; e; e = G.edge[e].next) {
            int v = G.edge[e].head;
            if (!G.vertex[v].ok) continue;
            if (G.vertex[v].dis > G.vertex[u].dis + 1) {
                G.vertex[v].dis = G.vertex[u].dis + 1;
                q.push(v);
            }
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
    BFS();
    if (G.vertex[t].dis == inf) G.vertex[t].dis = -1;
    std::cout << G.vertex[t].dis;
    return 0;
}