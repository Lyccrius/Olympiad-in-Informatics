#include <iostream>
#include <queue>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 1e5;
const int maxM = 5e5;
const int inf = 1e9;

int n, m;
int v;
int x, y, z;

namespace graph {
    struct Vertex {
        int head;
        int dis;
        int inq;
    } vertex[maxN * 3 + 10];

    struct Edge {
        int head;
        int next;
        int weight;
    } edge[maxM * 6 + maxN * 2 + 10];

    int ecnt;

    void addEdge(int tail, int head, int weight) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].weight = weight;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    void SPFA(int s) {
        for (int i = 1; i <= n * 3; i++) vertex[i].dis = -inf;
        vertex[s].dis = 0;
        vertex[s].inq = true;
        std::queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            vertex[u].inq = false;
            for (int e = vertex[u].head; e; e = edge[e].next) {
                int v = edge[e].head;
                int w = edge[e].weight;
                if (vertex[v].dis < vertex[u].dis + w) {
                    vertex[v].dis = vertex[u].dis + w;
                    if (!vertex[v].inq) {
                        vertex[v].inq = true;
                        q.push(v);
                    }
                }
            }
        }
        return;
    }
}

int main() {
    promote();
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) std::cin >> v, graph::addEdge(i, i + n, -v), graph::addEdge(i + n, i + n + n, v);
    for (int i = 1; i <= m; i++) {
        std::cin >> x >> y >> z;
        if (z == 1) {
            graph::addEdge(x, y, 0);
            graph::addEdge(x + n, y + n, 0);
            graph::addEdge(x + n + n, y + n + n, 0);
        } else {
            graph::addEdge(x, y, 0);
            graph::addEdge(x + n, y + n, 0);
            graph::addEdge(x + n + n, y + n + n, 0);
            graph::addEdge(y, x, 0);
            graph::addEdge(y + n, x + n, 0);
            graph::addEdge(y + n + n, x + n + n, 0);
        }
    }
    graph::SPFA(1);
    std::cout << graph::vertex[n + n + n].dis << '\n';
    return 0;
}