#include <iostream>
#include <vector>
#include <map>

typedef std::pair<int, int> pii;
typedef std::vector<pii> vpc;
typedef std::map<int, int> mii;
typedef std::map<int, mii> mmp;

const int maxN = 1e5;
const int logN = 17;

int n;
int x, y;
int k;

namespace graph {
    struct Vertex {
        int head;
        int next;
        int dep;
        int dif;
        int pre;
    } vertex[maxN * 10];

    vpc edges;

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

    struct SparseTable {
        struct Node {
            int f;
        } node[maxN + 10][logN + 5];
    } ST;

    mmp ans;

    void DFS1(int u, int from) {
        vertex[u].dep = vertex[from].dep + 1;
        ST.node[u][0].f = from;
        for (int p = 1; p <= logN; p++) {
            ST.node[u][p].f = ST.node[ST.node[u][p - 1].f][p - 1].f;
        }
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            DFS1(v, u);
        }
        return;
    }

    int LCA(int u, int v) {
        if (vertex[u].dep < vertex[v].dep) std::swap(u, v);
        for (int p = logN; p >= 0; p--) {
            if (vertex[ST.node[u][p].f].dep >= vertex[v].dep) {
                u = ST.node[u][p].f;
            }
        }
        if (u == v) return u;
        for (int p = logN; p >= 0; p--) {
            if (ST.node[u][p].f != ST.node[v][p].f) {
                u = ST.node[u][p].f;
                v = ST.node[v][p].f;
            }
        }
        return ST.node[u][0].f;
    }

    void travel(int x, int y) {
        int r = LCA(x, y);
        vertex[x].dif++;
        vertex[y].dif++;
        vertex[r].dif--;
        vertex[r].dif--;
        return;
    }

    void DFS2(int u, int from) {
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            DFS2(v, u);
            vertex[u].pre += vertex[v].pre;
        }
        vertex[u].pre += vertex[u].dif;
        ans[u][from] = vertex[u].pre;
        ans[from][u] = vertex[u].pre;
        return;
    }
}

int main() {
    std::cin >> n;
    for (int i = 1; i < n; i++) {
        std::cin >> x >> y;
        graph::edges.push_back(std::make_pair(x, y));
        graph::addEdge(x, y);
        graph::addEdge(y, x);
    }
    graph::DFS1(1, 0);
    std::cin >> k;
    for (int i = 1; i <= k; i++) {
        std::cin >> x >> y;
        graph::travel(x, y);
    }
    graph::DFS2(1, 0);
    for (int i = 1; i < n; i++) {
        pii e = graph::edges[i - 1];
        std::cout << graph::ans[e.first][e.second] << ' ';
    }
    return 0;
}