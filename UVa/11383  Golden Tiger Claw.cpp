#include <iostream>

const int maxN = 500;
const int inf = 1e9 + 10;

int n;
int a[maxN + 10][maxN + 10];

namespace graph {
    struct Vertex {
        int vis;
        int head;
        int match;
        int expect;
        int slack;
    } vertex[2 * maxN + 10], e;

    struct Edge {
        int head;
        int next;
        int weight;
    } edge[maxN * maxN + 10];

    int ecnt;

    void init() {
        for (int i = 1; i <= 2 * n; i++) vertex[i] = e;
        ecnt = 0;
        return;
    }

    void addEdge(int tail, int head, int weight) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        edge[ecnt].weight = weight;
        vertex[tail].head = ecnt;
        return;
    }

    bool DFS(int u) {
        vertex[u].vis = true;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            int w = edge[e].weight;
            int gap = vertex[u].expect + vertex[v].expect - w;
            if (vertex[v].vis) continue;
            if (gap == 0) {
                vertex[v].vis = true;
                if (vertex[v].match == 0 || DFS(vertex[v].match)) {
                    vertex[v].match = u;
                    return true;
                }
            } else vertex[v].slack = std::min(vertex[v].slack, gap);
        }
        return false;
    }

    void KM() {
        for (int u = 1; u <= n; u++) vertex[u].expect = 0;
        for (int u = 1; u <= n; u++) vertex[u + n].expect = 0;
        for (int u = 1; u <= n; u++) for (int e = vertex[u].head; e; e = edge[e].next) vertex[u].expect = std::max(vertex[u].expect, edge[e].weight); 
        for (int u = 1; u <= n; u++) {
            for (int v = 1; v <= n; v++) vertex[v].vis = false;
            for (int v = 1; v <= n; v++) vertex[v + n].vis = false;
            for (int v = 1; v <= n; v++) vertex[v + n].slack = inf;
            while (!DFS(u)) {
                int delta = inf;
                for (int v = 1; v <= n; v++) if (vertex[v + n].vis == false) delta = std::min(delta, vertex[v + n].slack);
                for (int v = 1; v <= n; v++) if (vertex[v + n].vis) vertex[v + n].expect += delta; else vertex[v + n].slack -= delta;
                for (int v = 1; v <= n; v++) if (vertex[v].vis) vertex[v].expect -= delta;
                for (int v = 1; v <= n; v++) vertex[v + n].vis = false;
                for (int v = 1; v <= n; v++) vertex[v].vis = false;
            }
        }
        return;
    }
}

void mian() {
    graph::init();
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) std::cin >> a[i][j];
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) graph::addEdge(i, j + n, a[i][j]);
    graph::KM();
    int ans = 0;
    for (int i = 1; i < n; i++) std::cout << graph::vertex[i].expect << ' '; std::cout << graph::vertex[n].expect << '\n';
    for (int i = 1; i < n; i++) std::cout << graph::vertex[i + n].expect << ' '; std::cout << graph::vertex[n + n].expect << '\n';
    for (int i = 1; i <= n; i++) ans += graph::vertex[i].expect;
    for (int i = 1; i <= n; i++) ans += graph::vertex[i + n].expect;
    std::cout << ans << '\n';
    return;
}

int main() {
    while (scanf("%d", &n) != EOF) mian();
    return 0;
}