#include <iostream>
#include <algorithm>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 5e4;
const int inf = 1e9;

int n;
int a, b;
int x, y = inf, z = inf;

namespace tree {
    struct Vertex {
        int head;
        int size;
        int dist;
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

    void DFS(int u, int from) {
        //printf("DFSing %d\n", u);
        vertex[u].size = 1;
        vertex[u].dist = 0;
        int maxPart = 0;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            DFS(v, u);
            vertex[u].size += vertex[v].size;
            vertex[u].dist += vertex[v].size + vertex[v].dist;
            maxPart = std::max(maxPart, vertex[v].size);
        }
        maxPart = std::max(maxPart, n - vertex[u].size);
        if (z > maxPart || (z == maxPart && u <= x)) {
            z = maxPart;
            y = vertex[u].dist;
            x = u;
        }
        //printf("size[%d] = %d\n", u, vertex[u].size);
        //printf("dist[%d] = %d\n", u, vertex[u].dist);
        return;
    }
}

int main() {
    promote();
    std::cin >> n;
    for (int i = 1; i < n; i++) std::cin >> a >> b, tree::addEdge(a, b), tree::addEdge(b, a);
    tree::DFS(1, 0);
    tree::DFS(x, 0);
    std::cout << x << ' ' << y << '\n';
    return 0;
}