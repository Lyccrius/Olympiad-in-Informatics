#include <iostream>
#include <algorithm>

typedef long long lxl;

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 1e5;
const lxl inf = 1e10 + 10;

int n, m; char type[10];
int p[maxN + 10];
int u, v;
int a, x, b, y;

namespace graph {
    struct Vertex {
        int head;
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
    } edge[maxN * 2 + 10];

    int ecnt;

    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    lxl f[maxN + 10][2];

    void DFS(int u, int from) {
        f[u][0] = 0;
        f[u][1] = 0;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            DFS(v, u);
            f[u][0] += f[v][1];
            f[u][1] += std::min(f[v][0], f[v][1]);
        }
        f[u][1] += p[u];
        if (u == a) f[u][!x] = inf;
        if (u == b) f[u][!y] = inf;
        return;
    }
}

int main() {
	std::cin >> n >> m >> type;
	for (int i = 1; i <= n; i++) std::cin >> p[i];
	for (int i = 1; i < n; i++) std::cin >> u >> v, graph::addEdge(u, v), graph::addEdge(v, u);
    for (int i = 1; i <= m; i++) {
        std::cin >> a >> x >> b >> y;
        graph::DFS(1, 0);
        lxl ans = std::min(graph::f[1][0], graph::f[1][1]);
        if (ans >= inf) ans = -1;
        std::cout << ans << '\n';
    }
	return 0;
}