#include <iostream>
#include <queue>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef long long lxl;

const lxl inf = 1e12;
const int maxN = 1e5;
const int maxM = 1e5;

int n, m;
int a, b, w;

namespace graph {
    struct Vertex {
        int vertex;
        int from;
        int head;
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
    } edge[maxM * 2 + 10];

    int ecnt;

    void addEdge(int tail, int head, int weight) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].weight = weight;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    void Dijkstra(int s) {
        for (int i = 1; i <= n; i++) vertex[i].vertex = i;
        for (int i = 1; i <= n; i++) vertex[i].dis = inf;
        vertex[s].dis = 0;
        std::priority_queue<Vertex> q;
        q.push(vertex[s]);
        while (!q.empty()) {
            int u = q.top().vertex;
            q.pop();
            if (vertex[u].vis) continue;
            vertex[u].vis = true;
            for (int e = vertex[u].head; e; e = edge[e].next) {
                int v = edge[e].head;
                int w = edge[e].weight;
                if (vertex[v].dis > vertex[u].dis + w) {
                    vertex[v].dis = vertex[u].dis + w;
                    vertex[v].from = u;
                    q.push(vertex[v]);
                }
            }
        }
        return;
    }

    void print(int u) {
        if (u == 0) return;
        print(vertex[u].from);
        std::cout << u << ' ';
        return;
    }
}

int main() {
    promote();
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) std::cin >> a >> b >> w, graph::addEdge(a, b, w), graph::addEdge(b, a, w);
    graph::Dijkstra(1);
    if (graph::vertex[n].dis == inf) std::cout << -1;
    else graph::print(n);
    return 0;
}