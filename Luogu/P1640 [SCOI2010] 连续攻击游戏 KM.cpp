#include <iostream>

const int maxN = 1e6;
const int maxA = 1e4;

int N;
int a, b;

namespace graph {
    struct Vertex {
        int vis;
        int head;
        int match;
    } vertex[maxA + maxN + 10];

    struct Edge {
        int head;
        int next;
    } edge[maxN * 2 * 2 + 10];

    int ecnt;

    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    void init() {
        for (int i = 1; i <= maxA + N; i++) vertex[i].vis = false;
        return;
    }

    bool KM(int u, int now) {
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (vertex[v].vis == now) continue;
            vertex[v].vis = now;
            if (vertex[v].match == 0 || KM(vertex[v].match, now)) {
                vertex[v].match = u;
                return true;
            }
        }
        return false;
    }
}

int main() {
    std::cin >> N;
    for (int i = 1; i <= N; i++) {
        std::cin >> a >> b;
        graph::addEdge(a, i + maxA);
        graph::addEdge(b, i + maxA);
        graph::addEdge(i + maxA, a);
        graph::addEdge(i + maxA, b);
    }
    for (int i = 1; i <= maxA; i++) {
        //graph::init();
        if (!graph::KM(i, i)) {
            std::cout << i - 1;
            return 0;
        }
    }
    std::cout << maxA;
    return 0;
}