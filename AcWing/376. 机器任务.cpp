#include <iostream>
#include <cstring>

const int maxN = 100;
const int maxM = 100;
const int maxK = 100;

int N, M, K;
int j, a, b;
int ans;

namespace graph {
    struct Vertex {
        bool vis;
        int match;
        int head;
    } vertex[maxN + 10];
    
    struct Edge {
        int head;
        int next;
    } edge[maxK * 2 + 10];

    int ecnt;

    bool adjacency[maxN + 10][maxM + 10];

    void addEdge(int tail, int head) {
        /*
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        */
        adjacency[tail][head] = true;
        return;
    }

    bool KM(int u) {
        //for (int e = vertex[u].head; e; e = edge[e].next) {
        //    int v = edge[e].head;
        for (int v = 1; v < M; v++) if (adjacency[u][v]) {
            if (vertex[v].vis) continue;
            vertex[v].vis = true;
            int t = vertex[v].match;
            if (t == 0 || KM(t)) {
                vertex[v].match = u;
                return true;
            }
        }
        return false;
    }

    void init() {
        for (int i = 1; i <= maxN; i++) vertex[i].vis = false;
        return;
    }
}

void init() {
    for (int i = 1; i <= maxN; i++) graph::vertex[i].match = 0;
    for (int i = 1; i <= maxN; i++) graph::vertex[i].head = 0;
    std::memset(graph::adjacency, 0, sizeof(graph::adjacency));
    graph::ecnt = 0;
    ans = 0;
    return;
}

void mian() {
    init();
    for (int i = 1; i <= K; i++) {
        std::cin >> j >> a >> b;
        if (a == 0 || b == 0) continue;
        graph::addEdge(a, b);
        //graph::addEdge(b + N, a);
    }
    for (int i = 1; i < N; i++) {
        graph::init();
        if (graph::KM(i)) ans++;
    }
    std::cout << ans << '\n';
    return;
}

int main() {
    while (std::cin >> N && N) std::cin >> M >> K, mian();
    return 0;
}