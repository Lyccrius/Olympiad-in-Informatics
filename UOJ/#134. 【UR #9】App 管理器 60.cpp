#include <iostream>

const int maxN = 5000;
const int maxM = 5000;

int n, m;
int a[maxM + 10], b[maxM + 10], t[maxM + 10];
int c[maxM + 10], d[maxM + 10];

namespace graph {
    struct Vertex {
        int head;
        int dep;
        int dfn;
        int low;
        int ins;
        int vis;
    } vertex[maxN + 10], e;

    struct Edge {
        int head;
        int next;
        int i;
        int c;
    } edge[2 * maxM + 10];

    int ecnt;
    int scnt;
    int dfn;

    void addEdge(int tail, int head, int i, int c) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        edge[ecnt].i = i;
        edge[ecnt].c = c;
        vertex[tail].head = ecnt;
        return;
    }

    void DFS(int u) {
        vertex[u].vis = true;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            int i = edge[e].i;
            if (d[i]) continue;
            d[i] = true;
            c[i] = edge[e].c;
            if (vertex[v].dfn) continue;
            DFS(v);
        }
        return;
    }

    void Tarjan(int u) {
        dfn++;
        vertex[u].dfn = dfn;
        vertex[u].low = dfn;
        vertex[u].ins = true;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (!vertex[v].dfn) {
                Tarjan(v);
                vertex[u].low = std::min(vertex[u].low, vertex[v].low);
            } else if (vertex[v].ins) {
                vertex[u].low = std::min(vertex[u].low, vertex[v].dfn);
            }
        }
        if (vertex[u].dfn == vertex[u].low) scnt++;
        vertex[u].ins = false;
        return;
    }

    void clear() {
        for (int i = 1; i <= n; i++) vertex[i] = e;
        ecnt = 0;
        scnt = 0;
        dfn = 0;
        return;
    }
}

namespace t123 {
    const int maxN = 17;
    const int maxM = 17;

    void check() {
        graph::clear();
        for (int i = 1; i <= m; i++) {
            if (c[i]) graph::addEdge(b[i], a[i], i, 1);
            else graph::addEdge(a[i], b[i], i, 0);
        }
        for (int i = 1; i <= n; i++) if (!graph::vertex[i].dfn) graph::Tarjan(i);
        if (graph::scnt > 1) return;
        for (int i = 1; i <= m; i++) std::cout << c[i] << '\n';
        exit(0);
    }

    void DFS(int now) {
        if (now > m) {
            check();
            return;
        }
        c[now] = 0;
        DFS(now + 1);
        if (t[now]) return;
        c[now] = 1;
        DFS(now + 1);
        return;
    }

    void mian() {
        DFS(1);
        return;
    }
}

namespace t456 {
    const int maxN = 5000;
    const int maxM = 5000;

    void mian() {
        for (int i = 1; i <= m; i++) graph::addEdge(a[i], b[i], i, 0), graph::addEdge(b[i], a[i], i, 1);
        graph::DFS(1);
        for (int i = 1; i <= m; i++) std::cout << c[i] << '\n';
        return;
    }
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) std::cin >> a[i] >> b[i] >> t[i];
    if (n <= 17 && m <= 17) t123::mian();
    else t456::mian();
    return 0;
}