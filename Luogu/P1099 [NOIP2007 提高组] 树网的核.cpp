#include <iostream>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 300;
const int maxS = 1e3;
const int maxW = 1e3;

int n, s;
int u, v, w;

int end;
int ans = maxN * maxW + 10;

namespace treenetwork {
    struct Vertex {
        int head;
        int from;
        int dis;
        int ondiam;
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
        int weight;
    } edge[maxN * 2 + 10];

    int ecnt;

    void addEdge(int tail, int head, int weight) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].weight = weight;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    void DFS(int u, int from) {
        vertex[u].from = from;
        if (vertex[u].dis > vertex[end].dis) end = u;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            int w = edge[e].weight;
            if (v == from || vertex[v].ondiam) continue;
            vertex[v].dis = vertex[u].dis + w;
            DFS(v, u);
        }
        return;
    }

    void mian() {
        vertex[1].dis = 1; DFS(1, 0);
        vertex[end].dis = 0; DFS(end, 0);
        for (int i = end, j = end; i; i = vertex[i].from) {
            while (vertex[j].dis - vertex[i].dis > s) j = vertex[j].from;
            ans = std::min(ans, std::max(vertex[end].dis - vertex[j].dis, vertex[i].dis));
        }
        for (int i = end; i; i = vertex[i].from) vertex[i].ondiam = true;
        for (int i = end; i; i = vertex[i].from) vertex[i].dis = 0, DFS(i, vertex[i].from);
        for (int i = 1; i <= n; i++) ans = std::max(ans, vertex[i].dis);
        std::cout << ans << '\n';
    }
}

int main() {
    promote();
    std::cin >> n >> s;
    for (int i = 1; i < n; i++) std::cin >> u >> v >> w, treenetwork::addEdge(u, v, w), treenetwork::addEdge(v, u, w);
    treenetwork::mian();
    return 0;
}