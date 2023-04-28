#include <iostream>
#include <map>

typedef unsigned long long ull;
typedef std::map<ull, int> mui;

const int maxM = 50;
const int maxN = 50;

int M;
int N;
int F[maxN + 10];
mui S;
ull res[maxN + 10];
int ans;

namespace graph {
    struct Vertex {
        int head;
        ull hash;
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
    } edge[2 * maxN + 10];

    int ecnt;
    int root;

    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    void init() {
        for (int i = 1; i <= N; i++) vertex[i].head = 0;
        ecnt = 0;
        return;
    }

    ull shift(ull x) {
        x ^= x << 13;
        x ^= x >> 7;
        x ^= x << 17;
        return x;
    }

    void DFS(int u, int from) {
        vertex[u].hash = 1;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            DFS(v, u);
            vertex[u].hash += shift(vertex[v].hash);
        }
        return;
    }
}

void mian(int id) {
    graph::init();
    std::cin >> N;
    for (int i = 1; i <= N; i++) {
        std::cin >> F[i];
        if (F[i] == 0) continue;
        graph::addEdge(i, F[i]);
        graph::addEdge(F[i], i);
    }
    for (int i = 1; i <= N; i++) {
        graph::DFS(i, 0);
        res[i] = graph::vertex[i].hash;
    }
    ans = id;
    for (int i = 1; i <= N; i++) {
        if (!S[res[i]]) S[res[i]] = id;
        ans = std::min(ans, S[res[i]]);
    }
    std::cout << ans << '\n';
    return;
}

int main() {
    std::cin >> M;
    for (int i = 1; i <= M; i++) mian(i);
    return 0;
}