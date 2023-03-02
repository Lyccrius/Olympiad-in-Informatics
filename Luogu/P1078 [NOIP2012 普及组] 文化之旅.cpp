#include <iostream>
#include <set>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 100;
const int maxK = 100;
const int maxM = 10000;
const int maxD = 1000;
const int inf = 1e9 + 10;

int N, K, M, S, T;
int C[maxN + 10];
int a[maxK + 10][maxK + 10];
int u, v, d;
int ans = inf;

namespace graph {
    struct Vertex {
        int head;
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

    int vis[maxN + 10];
    int cnt[maxK + 10];

    bool check(int u) {
        if (vis[u]) return false;
        if (cnt[C[u]]) return false;
        for (int i = 1; i <= K; i++) {
            if (!cnt[i]) continue;
            if (a[C[u]][i]) return false;
        }
        return true;
    }

    void DFS(int u, int res) {
        if (u == S) {
            ans = std::min(ans, res);
            return;
        }
        if (ans < res) {
            return;
        }
        vis[u] = true;
        cnt[C[u]]++;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            int w = edge[e].weight;
            if (!check(v)) continue;
            DFS(v, res + w);
        }
        vis[u] = false;
        cnt[C[u]]--;
        return;
    }
}

int main() {
    promote();
    std::cin >> N >> K >> M >> S >> T;
    for (int i = 1; i <= N; i++) std::cin >> C[i];
    for (int i = 1; i <= K; i++) for (int j = 1; j <= K; j++) std::cin >> a[i][j];
    for (int i = 1; i <= M; i++) std::cin >> u >> v >> d, graph::addEdge(u, v, d), graph::addEdge(v, u, d);
    graph::DFS(T, 0);
    if (ans == inf) ans = -1;
    std::cout << ans << '\n';
    return 0;
}