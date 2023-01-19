#include <iostream>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 5e5;
const int maxM = 5e5;

int N, M, S;
int x, y;
int a, b;
int ans[maxM + 10];

namespace tree {
    struct Vertex {
        int headE;
        int headQ;
        int fa;
        bool vis;
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
    } edge[maxN * 2 + 10];

    int ecnt;

    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].headE;
        vertex[tail].headE = ecnt;
        return;
    }

    struct Query {
        int id;
        int other;
        int next;
    } query[maxM * 2 + 10];

    int qcnt;

    void addQuery(int id, int tail, int head) {
        qcnt++;
        query[qcnt].id = id;
        query[qcnt].other = head;
        query[qcnt].next = vertex[tail].headQ;
        vertex[tail].headQ = qcnt;
        return;
    }

    struct DisjointSetUnion {
        int Find(int u) {
            if (vertex[u].fa == u) return u;
            return vertex[u].fa = Find(vertex[u].fa);
        }

        void Union(int u, int v) {
            u = Find(u);
            v = Find(v);
            vertex[u].fa = v;
            return;
        }
    } DSU;

    void DFS(int u, int from) {
        vertex[u].fa = u;
        vertex[u].vis = true;
        for (int e = vertex[u].headE; e; e = edge[e].next) {
            int v = edge[e].head;
            if (vertex[v].vis) continue;
            DFS(v, u);
            DSU.Union(v, u);
        }
        for (int q = vertex[u].headQ; q; q = query[q].next) {
            int i = query[q].id;
            int v = query[q].other;
            if (!vertex[v].vis) continue;
            ans[i] = DSU.Find(v);
        }
        return;
    }
}

int main() {
    promote();
    std::cin >> N >> M >> S;
    for (int i = 1; i < N; i++) std::cin >> x >> y, tree::addEdge(x, y), tree::addEdge(y, x);
    for (int i = 1; i <= M; i++) std::cin >> a >> b, tree::addQuery(i, a, b), tree::addQuery(i, b, a);
    tree::DFS(S, 0);
    for (int i = 1; i <= M; i++) std::cout << ans[i] << '\n';
    return 0;
}