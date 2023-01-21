#include <iostream>
#include <algorithm>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 2000;
const int inf = 2147483647;

int n;
int d[maxN + 10][maxN + 10];

namespace graph {
    struct Vertex {
        int from;
        int head;
        int vis;
        int dis;
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

    void Prim() {
        //for (int i = 1; i <= n; i++) vertex[i].vertex = i;
        for (int i = 1; i <= n; i++) vertex[i].dis = inf;
        vertex[1].dis = 0;
        vertex[0].dis = inf;
        while (true) {
            int u = 0;
            for (int i = 1; i <= n; i++) if (!vertex[i].vis && vertex[i].dis < vertex[u].dis) u = i;
            if (!u) break;
            //printf("%d\n", u);
            vertex[u].vis = true;
            if (u != 1) {
                addEdge(u, vertex[u].from, vertex[u].dis);
                addEdge(vertex[u].from, u, vertex[u].dis);
            }
            for (int v = 1; v <= n; v++) {
                if (vertex[v].vis) continue;
                int w = d[u][v];
                if (vertex[v].dis > w) {
                    vertex[v].dis = w;
                    vertex[v].from = u;
                }
            }
        }
        //printf("prim end\n");
        return;
    }

    void DFS(int u, int from) {
        //printf("DFSing %d from %d: %d\n", u, from, vertex[u].dis);
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            int w = edge[e].weight;
            //printf("v = %d, w = %d\n", v, w);
            if (v == from) continue;
            //if (c[u][v] != w) continue;
            vertex[v].dis = vertex[u].dis + w;
            DFS(v, u);
        }
        return;
    }

    void mian() {
        Prim();
        for (int i = 1; i <= n; i++) {
            vertex[i].dis = 0;
            DFS(i, 0);
            for (int j = 1; j <= n; j++) {
                if (vertex[j].dis != d[i][j]) {
                    std::cout << "NO\n";
                    //printf("vertex[%d].dis = %d != d[%d][%d] = %d\n", j, vertex[j].dis, i, j, d[i][j]);
                    return;
                }
            }
        }
        std::cout << "YES\n";
        return;
    }
}

int main() {
    promote();
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            std::cin >> d[i][j];
            if (i != j && d[i][j] == 0) {std::cout << "NO\n"; return 0;}
            if (i == j && d[i][j] != 0) {std::cout << "NO\n"; return 0;}
            //if (i != j) graph::addEdge(i, j, d[i][j]);
        }
    }
    graph::mian();
    return 0;
}