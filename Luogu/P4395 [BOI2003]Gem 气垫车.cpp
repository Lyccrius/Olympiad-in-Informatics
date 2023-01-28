#include <iostream>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 10000;
const int inf = 1e9;

int n;
int u, v;
int f[maxN + 10][5];
int ans = 0;

namespace tree {
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

    void DFS(int u, int from) {
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            DFS(v,u);
            for (int i = 1; i <= 4; i++) {
                int t = inf;
                for (int j = 1; j <= 4; j++) {
                    if (t > f[v][j] && i != j) {
                        t = f[v][j];
                    }
                }
                f[u][i] += t;
            }
        }
        for (int i = 1; i <= 4; i++) f[u][i] += i;
        return;
    }
}

int main() {
    std::cin >> n;
    for (int i = 1; i < n; i++) {
        std::cin >> u >> v;
        tree::addEdge(u, v);
        tree::addEdge(v, u);
    }
    tree::DFS(1, 0);
    ans = inf;
    for (int i = 1; i <= 4; i++) ans = std::min(ans, f[1][i]);
    std::cout << ans << '\n';
    return 0;
}