#include <iostream>
#include <vector>

typedef std::vector<int> vic;

const int maxN = 1000;

int n, b;
int u, v;

namespace graph {
    struct Vertex {
        int head;
        int bel;
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

    vic s;
    vic c;

    void DFS(int u, int from) {
        int bak = s.size();
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            DFS(v, u);
            int del = s.size() - bak;
            if (del >= b) {
                c.push_back(u);
                while (s.size() > bak) {
                    vertex[s.back()].bel = c.size();
                    s.pop_back();
                }
            }
        }
        s.push_back(u);
        return;
    }
}

int main() {
    std::cin >> n >> b;
    for (int i = 1; i <= n - 1; i++) std::cin >> u >> v, graph::addEdge(u, v), graph::addEdge(v, u);
    graph::DFS(1, 0);
    while (graph::s.size()) graph::vertex[graph::s.back()].bel = graph::c.size(), graph::s.pop_back();
    std::cout << graph::c.size() << '\n';
    for (int i = 1; i <= n; i++) std::cout << graph::vertex[i].bel << ' '; std::cout << '\n';
    for (auto i : graph::c) std::cout << i << ' '; std::cout << '\n';
    return 0;
}