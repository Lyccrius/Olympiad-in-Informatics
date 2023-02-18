#include <iostream>
#include <algorithm>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
}

const int maxN = 2e4;
const int maxM = 1e5;
const int inf = 1e9;

int N, M;
int a, b, c;

namespace graph {
    struct Vertex {
        int head;
        int vis;
        int col;
    };

    struct Edge {
        int head;
        int next;
        int weight;
    };

    Vertex vertex[maxN + 10];
    Edge edge[maxM * 2 + 10];
    int ecnt;

    void addEdge(int tail, int head, int weight) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].weight = weight;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    bool DFS(int u, int col, int maxW) {
        vertex[u].vis = true;
        vertex[u].col = col;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            int w = edge[e].weight;
            if (w <= maxW) continue;
            if (vertex[v].vis) {
                if (vertex[u].col == vertex[v].col) {
                    return false;
                }
            } else {
                if (!DFS(v, col ^ 1, maxW)) {
                    return false;
                }
            }
        }
        return true;
    }

    bool check(int x) {
        for (int u = 1; u <= N; u++) vertex[u].vis = false;
        for (int u = 1; u <= N; u++) {
            if (!vertex[u].vis) {
                if (!DFS(u, 1, x)) {
                    return false;
                }
            }
        }
        return true;
    }
}

int main() {
    promote();
    std::cin >> N >> M;
    int maxC = 0;
    for (int i = 1; i <= M; i++) {
        std::cin >> a >> b >> c;
        graph::addEdge(a, b, c);
        graph::addEdge(b, a, c);
        maxC = std::max(maxC, c);
    }
    int l = 0;
    int r = maxC;
    while (l < r) {
        int mid = (l + r) / 2;
        if (graph::check(mid)) r = mid;
        else l = mid + 1;
    }
    std::cout << l;
    return 0;
}