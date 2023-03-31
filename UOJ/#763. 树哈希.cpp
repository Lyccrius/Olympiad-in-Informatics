#include <iostream>
#include <set>

typedef unsigned long long ull;
typedef std::set<ull> sut;

const int maxN = 1e6;

int n;
int a, b;
sut s;

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

    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
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
        s.insert(vertex[u].hash);
        return;
    }
}

int main() {
    std::cin >> n;
    for (int i = 1; i < n; i++) {
        std::cin >> a >> b;
        graph::addEdge(a, b);
        graph::addEdge(b, a);
    }
    graph::DFS(1, 0);
    std::cout << s.size() << '\n';
    return 0;
}