#include <iostream>
#include <queue>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 1e5;
const int maxM = 2e5;

int n, m;
int u, v, w;
double f[maxN + 10];

namespace graph {
    struct Vertex {
        int head;
        int cnt;
        int deg;
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
        edge[ecnt].weight = weight;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        vertex[head].cnt++;
        vertex[head].deg++;
        return;
    }

    void mian() {
        std::queue<int> q;
        q.push(n);
        f[n] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int e = vertex[u].head; e; e = edge[e].next) {
                int v = edge[e].head;
                int w = edge[e].weight;
                f[v] += (f[u] + w) / vertex[v].cnt;
                vertex[v].deg--;
                if (!vertex[v].deg) q.push(v);
            }
        }
        printf("%.2lf", f[1]);
        return;
    }
}

int main() {
    promote();
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) std::cin >> u >> v >> w, graph::addEdge(v, u, w);
    graph::mian();
    return 0;
}