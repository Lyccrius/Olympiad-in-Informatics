#include <iostream>

const int maxN = 20;
const int inf = 1e9 + 10;

int n;
int p[maxN + 10][maxN + 10];
int q[maxN + 10][maxN + 10];

namespace graph {
    struct Vertex {
        int vis;
        int head;
        int match;
        int slack;
        int expect;
        int weight;
    } vertex[maxN + maxN + 10];

    struct Edge {
        int head;
        int next;
        int weight;
    } edge[maxN * maxN + 10];

    int ecnt;

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
            if (vertex[v].vis) continue;
            int gap = vertex[u].expect + vertex[v].expect - w;
            if (gap == 0) {
                vertex[v].vis = true;
                if (vertex[v].match == 0 || DFS(vertex[v].match)) {
                    vertex[v].match = u;
                    vertex[v].weight = w;
                    return true;
                }
            } else if (gap > 0) {
                vertex[v].slack = std::min(vertex[v].slack, gap);
            }
        }
    }

    int KM() {
        int ret = 0;
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
        for (int u = 1; u <= n; u++) ret += vertex[u + n].weight;
        return ret;
    }
}

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) std::cin >> p[i][j];
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) std::cin >> q[i][j];
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) graph::addEdge(i, j + n, p[i][j] * q[j][i]);
    std::cout << graph::KM() << '\n';
    return 0;
}