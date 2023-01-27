#include <iostream>
#include <algorithm>
#include <vector>

const int maxN = 1e5;

int N;
int a, b;
std::vector<int> res;
bool ok;

namespace graph {
    struct Vertex {
        int head;
        int from;
        int low;
        int dfn;
        int ins;
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

    int dfn;

    void DFS(int u, int from) {
        //printf("DFS %d from %d\n", u, from);
        vertex[u].dfn = ++dfn;
        vertex[u].from = from;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            if (!vertex[v].dfn) {
                DFS(v, u);
            } else {
                vertex[v].from = u;
                int w = v;
                do {
                    res.push_back(w);
                    w = vertex[w].from;
                } while (w != v);
                ok = true;
            }
            if (ok) return;
        }
        return;
    }
}

int main() {
    std::cin >> N;
    for (int i = 1; i <= N; i++) {
        std::cin >> a >> b;
        graph::addEdge(a, b);
        graph::addEdge(b, a);
    }
    graph::DFS(1, 0);
    std::sort(res.begin(), res.end());
    for (auto i : res) std::cout << i << ' ';
    return 0;
}