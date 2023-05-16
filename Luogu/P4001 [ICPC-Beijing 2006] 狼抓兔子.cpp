#include <iostream>
#include <queue>

typedef long long lxl;

const int maxN = 1000;
const int maxM = 1000;
const int maxW = 1e6;
const lxl inf = 1e18 + 10;

int n, m;
int w;

namespace graph {
    struct Vertex {
        int vertex;
        int head;
        int vis;
        lxl dis;

        Vertex() {
            head = -1;
            return;
        }

        bool operator<(const Vertex &other) const {
            return dis > other.dis;
        }
    } vertex[2 * maxN * maxM + 10];

    struct Edge {
        int head;
        int next;
        int weight;
    } edge[2 * 3 * maxN * maxM + 10];

    int ecnt;

    void addEdge(int tail, int head, int weight) {
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        edge[ecnt].weight = weight;
        vertex[tail].head = ecnt;
        ecnt++;
        return;
    }

    void Dijkstra(int s) {
        std::priority_queue<Vertex> q;
        for (int i = 0; i <= 2 * (n - 1) * (m - 1) + 1; i++) vertex[i].vertex = i;
        for (int i = 0; i <= 2 * (n - 1) * (m - 1) + 1; i++) vertex[i].vis = false;
        for (int i = 0; i <= 2 * (n - 1) * (m - 1) + 1; i++) vertex[i].dis = inf;
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
                    q.push(vertex[v]);
                }
            }
        }
        return;
    }
}

int getL(int i, int j) {
    if (j == 1) return 0;
    return (i - 1) * 2 * (m - 1) + (j - 1) * 2;
}

int getR(int i, int j) {
    if (j == m) return 2 * (n - 1) * (m - 1) + 1;
    return (i - 1) * 2 * (m - 1) + (j - 1) * 2 + 1;
}

int getU(int i, int j) {
    if (i == 1) return 2 * (n - 1) * (m - 1) + 1;
    return getR(i - 1, j);
}

int getD(int i, int j) {
    if (i == n) return 0;
    return getL(i, j + 1);
}

void add1(int i, int j, int w) {
    int u = getU(i, j);
    int v = getD(i, j);
    graph::addEdge(u, v, w);
    graph::addEdge(v, u, w);
    return;
}

void add2(int i, int j, int w) {
    int u = getL(i, j);
    int v = getR(i, j);
    graph::addEdge(u, v, w);
    graph::addEdge(v, u, w);
    return;
}

void add3(int i, int j, int w) {
    int u = getD(i, j);
    int v = getR(i, j);
    graph::addEdge(u, v, w);
    graph::addEdge(v, u, w);
    return;
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m - 1; j++) {
            std::cin >> w;
            add1(i, j, w);
        }
    }
    for (int i = 1; i <= n - 1; i++) {
        for (int j = 1; j <= m; j++) {
            std::cin >> w;
            add2(i, j, w);
        }
    }
    for (int i = 1; i <= n - 1; i++) {
        for (int j = 1; j <= m - 1; j++) {
            std::cin >> w;
            add3(i, j, w);
        }
    }
    graph::Dijkstra(0);
    std::cout << graph::vertex[2 * (n - 1) * (m - 1) + 1].dis << '\n';
    return 0;
}