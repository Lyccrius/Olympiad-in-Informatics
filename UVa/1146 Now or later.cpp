#include <iostream>
#include <deque>

typedef std::deque<int> diq;

const int maxN = 2000;
const int maxT = 1e7;

int n;
int e[maxN + 10], l[maxN + 10];

namespace graph {
    struct Vertex {
        int head;
        int dfn;
        int low;
        int ins;
        int bel;
    } vertex[2 * maxN + 10], e;

    struct Edge {
        int head;
        int next;
    } edge[4 * maxN * maxN + 10];

    int ecnt;
    int scnt;
    int dfn;
    diq s;

    void init() {
        for (int i = 1; i <= n; i++) vertex[i] = e;
        for (int i = 1; i <= n; i++) vertex[i + n] = e;
        ecnt = 0;
        scnt = 0;
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

    void addSCC(int u) {
        int v;
        scnt++;
        do {
            v = s.back();
            s.pop_back();
            vertex[v].ins = false;
            vertex[v].bel = scnt;
        } while (v != u);
        return;
    }

    void Tarjan(int u) {
        dfn++;
        vertex[u].dfn = dfn;
        vertex[u].low = dfn;
        vertex[u].ins = true;
        s.push_back(u);
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (!vertex[v].dfn) {
                Tarjan(v);
                vertex[u].low = std::min(vertex[u].low, vertex[v].low);
            } else if (vertex[v].ins) vertex[u].low = std::min(vertex[u].low, vertex[v].dfn);
        }
        if (vertex[u].low == vertex[u].dfn) addSCC(u);
        return;
    }
}

bool check(int mid) {
    graph::init();
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (std::abs(e[i] - e[j]) < mid) graph::addEdge(i, j + n), graph::addEdge(j, i + n);
            if (std::abs(e[i] - l[j]) < mid) graph::addEdge(i, j), graph::addEdge(j + n, i + n);
            if (std::abs(l[i] - e[j]) < mid) graph::addEdge(i + n, j + n), graph::addEdge(j, i);
            if (std::abs(l[i] - l[j]) < mid) graph::addEdge(i + n, j), graph::addEdge(j + n, i);
        }
    }
    for (int i = 1; i <= n; i++) if (!graph::vertex[i].dfn) graph::Tarjan(i);
    for (int i = 1; i <= n; i++) if (!graph::vertex[i + n].dfn) graph::Tarjan(i + n);
    for (int i = 1; i <= n; i++) if (graph::vertex[i].bel == graph::vertex[i + n].bel) return false;
    return true;
}

void mian() {
    for (int i = 1; i <= n; i++) std::cin >> e[i] >> l[i];
    int l = 0;
    int r = maxT;
    while (l < r) {
        int mid = (l + r + 1) / 2;
        if (check(mid)) l = mid;
        else r = mid - 1;
    }
    std::cout << l << '\n';
    return;
}

int main() {
    while (scanf("%d", &n) != EOF) mian();
    return 0;
}