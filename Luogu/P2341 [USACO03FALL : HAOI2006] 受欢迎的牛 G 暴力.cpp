#include <iostream>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 1e4;
const int maxM = 5e4;

int N, M;
int A, B;
int ans;

namespace graph {
    struct Vertex {
        int head;
        int vis;
        int star;
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
    } edge[maxM + 10];

    int ecnt;

    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    int cnt;

    bool DFS(int u) {
        if (vertex[u].star) return true;
        if (vertex[u].vis) return false;
        vertex[u].vis = true;
        cnt++;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (vertex[v].star) {
                vertex[u].star = true;
                return true;
            }
            if (DFS(v)) {
                vertex[u].star = true;
                return true;
            }
        }
        return false;
    }

    void solve(int u) {
        for (int i = 1; i <= N; i++) vertex[i].vis = false;
        cnt = 0;
        if (DFS(u)) {
            vertex[u].star = true;
            ans++;
        }
        if (cnt == N) {
            vertex[u].star = true;
            ans++;
        }
        return;
    }
}

int main() {
    promote();
    std::cin >> N >> M;
    for (int i = 1; i <= M; i++) {
        std::cin >> A >> B;
        graph::addEdge(B, A);
        graph::vertex[A].vis = true;
        graph::vertex[B].vis = true;
    }
    for (int i = 1; i <= N; i++) {
        if (graph::vertex[i].vis == false) {
            std::cout << 0 << '\n';
            return 0;
        }
    }
    for (int i = 1; i <= N; i++) graph::solve(i);
    std::cout << ans;
    return 0;
}