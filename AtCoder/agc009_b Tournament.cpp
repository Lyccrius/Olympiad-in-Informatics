#include <iostream>
#include <algorithm>
#include <vector>

typedef std::vector<int> vic;

const int maxN = 1e5;

int n;
int a[maxN + 10];

namespace graph {
    struct Vertex {
        int head;
        int f;
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

    void DFS(int u, int from) {
        vic t;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            DFS(v, u);
            t.push_back(vertex[v].f);
        }
        std::sort(t.begin(), t.end());
        for (auto i : t) {
            vertex[u].f = std::max(vertex[u].f, i) + 1;
        }
        return;
    }
}

int main() {
    std::cin >> n;
    for (int i = 2; i <= n; i++) {
        std::cin >> a[i];
        graph::addEdge(a[i], i);
        graph::addEdge(i, a[i]);
    }
    graph::DFS(1, 0);
    std::cout << graph::vertex[1].f << '\n';
    return 0;
}