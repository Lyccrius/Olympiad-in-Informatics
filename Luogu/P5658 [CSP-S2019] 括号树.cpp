#include <iostream>

typedef char chr;
typedef long long lxl;

const int maxN = 5e5;

int n;
chr c[maxN + 10];
int f[maxN + 10];
lxl ans;

namespace graph {
    struct Vertex {
        int head;
        int pre;
        lxl cnt;
        lxl res;
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
    } edge[maxN + 10];

    int ecnt;

    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    void DFS(int u, int from) {
        if (c[u] == '(') {
            vertex[u].pre = u;
            vertex[u].res = vertex[from].res;
        } else {
            vertex[u].pre = vertex[from].pre;
            vertex[u].res = vertex[from].res;
            if (vertex[u].pre) {
                vertex[u].cnt = vertex[f[vertex[u].pre]].cnt + 1;
                vertex[u].pre = vertex[f[vertex[u].pre]].pre;
                vertex[u].res += vertex[u].cnt;
            }
        }
        ans ^= vertex[u].res * u;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            DFS(v, u);
        }
        return;
    }
}

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> c[i];
    for (int i = 2; i <= n; i++) std::cin >> f[i];
    for (int i = 2; i <= n; i++) graph::addEdge(f[i], i);
    graph::DFS(1, 0);
    std::cout << ans;
    return 0;
}