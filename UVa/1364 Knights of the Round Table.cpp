#include <iostream>
#include <deque>

typedef std::deque<int> diq;

const int maxN = 1000;
const int maxM = 1000000;

int n, m;
int a[maxN + 10][maxN + 10];
int u, v;
int ans;

namespace graph {
    struct Vertex {
        int head;
        int dfn;
        int low;
        int bel;
        int col;
        int odd;
    } vertex[maxN + 10], e;

    struct Edge {
        int head;
        int next;
    } edge[2 * maxM + 10];

    int ecnt;
    int bcnt;
    int dfn;
    diq s;

    void init() {
        for (int i = 1; i <= n; i++) vertex[i] = e;
        ecnt = 0;
        bcnt = 0;
        dfn = 0;
        s.clear();
        return;
    }

    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    bool check(int u, int col) {
        if (vertex[u].col == col) return false;
        if (vertex[u].col) return true;
        vertex[u].col = col;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (vertex[v].bel != vertex[u].bel) continue;
            if (check(v, 3 - col)) return true;
        }
        return false;
    }

    void addVBCC(int u) {
        int v;
        diq b;
        bcnt++;
        do {
            v = s.back();
            s.pop_back();
            b.push_back(v);
            vertex[v].bel = bcnt;
            vertex[v].col = 0;
        } while (v != u);
        if (check(u, 1)) for (auto w : b) vertex[w].odd = true;
        return;
    }

    void DFS(int u, int from) {
        dfn++;
        vertex[u].dfn = dfn;
        vertex[u].low = dfn;
        s.push_back(u);
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            if (!vertex[v].dfn) {
                DFS(v, u);
                vertex[u].low = std::min(vertex[u].low, vertex[v].low);
                if (vertex[v].low >= vertex[u].dfn) {
                    s.push_back(u);
                    addVBCC(v);
                }
            } else vertex[u].low = std::min(vertex[u].low, vertex[v].dfn);
        }
        return;
    }
}

void mian() {
    graph::init();
    std::fill(a[0], a[0] + sizeof(a) / 8, 1);
    ans = 0;
    for (int i = 1; i <= m; i++) std::cin >> u >> v, a[u][v] = false, a[v][u] = false;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) if (a[i][j] && i != j) graph::addEdge(i, j);
    for (int i = 1; i <= n; i++) if (!graph::vertex[i].dfn) graph::DFS(i, 0);
    for (int i = 1; i <= n; i++) if (!graph::vertex[i].odd) ans++;
    std::cout << ans << '\n';
    return;
}

int main() {
    while (std::cin >> n >> m && n && m) mian();
    return 0;
}