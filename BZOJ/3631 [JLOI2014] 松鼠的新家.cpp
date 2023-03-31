#include <iostream>

const int maxN = 3e5;
const int logN = 19;

int n;
int a[maxN + 10];
int x, y, z;

namespace graph {
    struct Vertex {
        int head;
        int val;
        int dep;
        int fa;

        Vertex() {
            head = -1;
            return;
        }
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
    } edge[maxN * 2 + 10];

    int ecnt;

    void addEdge(int tail, int head) {
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        ecnt++;
        return;
    }

    struct SparseTable {
        struct Node {
            int fa;
        } node[maxN + 10][logN + 10];
    } ST;

    void DFS1(int u, int from) {
        vertex[u].dep = vertex[from].dep + 1;
        vertex[u].fa = from;
        ST.node[u][0].fa = from;
        //printf("DFS %d from %d\n", u, from);
        for (int p = 1; p <= logN; p++) {
            ST.node[u][p].fa = ST.node[ST.node[u][p - 1].fa][p - 1].fa;
            //printf("fa[%d][%d] = %d\n", u, p, ST.node[u][p].fa);
        }
        for (int e = vertex[u].head; ~e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            DFS1(v, u);
        }
        return;
    }

    int LCA(int u, int v) {
        if (vertex[u].dep < vertex[v].dep) std::swap(u, v);
        for (int p = logN; p >= 0; p--) {
            if (vertex[ST.node[u][p].fa].dep >= vertex[v].dep) {
                u = ST.node[u][p].fa;
            }
        }
        if (u == v) return u;
        for (int p = logN; p >= 0; p--) {
            if (ST.node[u][p].fa != ST.node[v][p].fa) {
                u = ST.node[u][p].fa;
                v = ST.node[v][p].fa;
            }
        }
        return ST.node[u][0].fa;
    }

    void DFS2(int u, int from) {
        for (int e = vertex[u].head; ~e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            DFS2(v, u);
            vertex[u].val += vertex[v].val;
        }
        return;
    }
}

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i < n; i++) {
        std::cin >> x >> y;
        graph::addEdge(x, y);
        graph::addEdge(y, x);
    }
    graph::DFS1(1, 0);
    for (int i = 1; i < n; i++) {
        x = a[i];
        y = a[i + 1];
        z = graph::LCA(x, y);
        graph::vertex[x].val++;
        graph::vertex[y].val++;
        graph::vertex[z].val--;
        graph::vertex[graph::vertex[z].fa].val--;
    }
    graph::DFS2(1, 0);
    for (int i = 2; i <= n; i++) graph::vertex[a[i]].val--;
    for (int i = 1; i <= n; i++) std::cout << graph::vertex[i].val << '\n';
    return 0;
}