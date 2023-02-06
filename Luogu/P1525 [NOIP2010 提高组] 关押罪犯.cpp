#include <iostream>

const int maxN = 2e4;
const int maxM = 1e5;

int N, M;
int a, b, c;

namespace graph {
    struct Vertex {
        int head;
        int vis;
        int col;
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
    
    void init() {
        for (int u = 1; u <= N; u++) {
            vertex[u].vis = false;
            vertex[u].col = 0;
        }
        return;
    }

    bool DFS(int u, int col, int lim) {
        vertex[u].vis = true;
        vertex[u].col = col;
        //printf("DFS(%d, %d, %d)\n", u, col, lim);
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            int w = edge[e].weight;
            if (w <= lim) continue;
            if (vertex[v].vis) {
                //printf("vertex[%d].vised\n", v);
                if (vertex[v].col == vertex[u].col) {
                    return false;
                }
            } else {
                //printf("DFS(%d, %d, %d) from %d\n", v, 3 - col, lim, u);
                if (!DFS(v, 3 - col, lim)) {
                    return false;
                }
            }
        }
        return true;
    }
}

bool check(int x) {
    graph::init();
    for (int u = 1; u <= N; u++) {
        if (!graph::vertex[u].vis) {
            if (!graph::DFS(u, 1, x)) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    std::cin >> N >> M;
    for (int i = 1; i <= M; i++) std::cin >> a >> b >> c, graph::addEdge(a, b, c), graph::addEdge(b, a, c);
    int l = 0;
    int r = 1e9;
    while (l < r) {
        int mid = (l + r) / 2;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }
    std::cout << l;
    return 0;
}