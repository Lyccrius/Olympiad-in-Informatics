#include <iostream>
#include <algorithm>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 300;

int n;
int W[maxN + 10];
int P[maxN + 10][maxN + 10];

namespace graph {
    struct Vertex {
        int fa;
    } vertex[maxN + 10];

    struct Edge {
        int tail;
        int head;
        int weight;

        bool operator<(const Edge &other) const {
            return weight < other.weight;
        }
    } edge[maxN + maxN * maxN + 10];

    int ecnt;

    void addEdge(int tail, int head, int weight) {
        ecnt++;
        edge[ecnt].tail = tail;
        edge[ecnt].head = head;
        edge[ecnt].weight = weight;
        return;
    }

    struct DisjiontSetUnion {
        int Find(int u) {
            if (u == vertex[u].fa) return u;
            return vertex[u].fa = Find(vertex[u].fa);
        }

        void Union(int u, int v) {
            u = vertex[u].fa;
            v = vertex[v].fa;
            vertex[u].fa = v;
            return;
        }
    } DSU;

    int Kruscal() {
        int ret = 0;
        int cnt = 0;
        for (int i = 1; i <= n; i++) vertex[i].fa = i;
        std::sort(edge + 1, edge + ecnt + 1);
        for (int i = 1; i <= ecnt; i++) {
            int u = edge[i].tail;
            int v = edge[i].head;
            int w = edge[i].weight;
            u = DSU.Find(u);
            v = DSU.Find(v);
            if (u == v) continue;
            DSU.Union(u, v);
            ret += w;
            cnt++;
            if (cnt == n) break;
        }
        return ret;
    }
}

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> W[i], graph::addEdge(0, i, W[i]);
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) std::cin >> P[i][j], graph::addEdge(i, j, P[i][j]);
    std::cout << graph::Kruscal();
    return 0;
}