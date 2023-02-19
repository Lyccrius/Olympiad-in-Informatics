#include <iostream>

const int maxN = 1e4;
const int maxM = 5e4;
const int maxQ = 3e4;
const int maxZ = 1e5;

int n, m;
int x, y, z;
int q;

namespace graph {
    struct Vertex {
        int head;
        int vis;
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
        edge[ecnt].next = vertex[tail].head;
        edge[ecnt].weight = weight;
        vertex[tail].head = ecnt;
        return;
    }

    void init() {
        for (int i = 1; i <= n; i++) vertex[i].vis = 0;
        return;
    }

    void DFS(int u, int lim) {
        vertex[u].vis = lim;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            int w = edge[e].weight;
            if (w < lim) continue;
            if (vertex[v].vis == lim) continue;
            DFS(v, lim);
        }
        return;
    }
}

bool check(int mid) {
    graph::DFS(x, mid);
    return graph::vertex[y].vis == mid;
}

void mian() {
    graph::init();
    std::cin >> x >> y;
    int l = 0;
    int r = maxZ;
    while (l < r) {
        int mid = (l + r + 1) / 2;
        if (check(mid)) l = mid;
        else r = mid - 1;
    }
    if (!check(l)) l = -1;
    std::cout << l << '\n';
    return;
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        std::cin >> x >> y >> z;
        graph::addEdge(x, y, z);
        graph::addEdge(y, x, z);
    }
    std::cin >> q;
    while (q--) mian();
    return 0;
}