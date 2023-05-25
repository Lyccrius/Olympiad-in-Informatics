#include <iostream>
#include <deque>

typedef std::deque<int> diq;

const int maxN = 365;
const int maxM = 1000;
const int maxG = 1e5;
const int maxC = 300;
const int maxD = 30000;
const int maxR = 100;
const int inf = maxN * maxM * maxR;

int n, m;
int g;
int c, d;
int x, l, r;
int s, t;
int S, T;

namespace graph {
    struct Vertex {
        int head;
        int dep;
        int cur;
        int i, o;

        Vertex() {
            head = -1;
            return;
        }
    } vertex[maxN + maxM + 10], e;

    struct Edge {
        int head;
        int next;
        int flow;
        int capacity;
    } edge[2 * (maxM + maxN * maxD + maxN + maxM) + 10];

    int ecnt;

    void init() {
        for (int i = 0; i <= n + m + 3; i++) vertex[i] = e;
        ecnt = 0;
        return;
    }

    void addEdge(int tail, int head, int flow, int capacity) {
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        edge[ecnt].flow = flow;
        edge[ecnt].capacity = capacity;
        vertex[tail].head = ecnt;
        ecnt++;
        return;
    }

    void AddEdge(int tail, int head, int flow, int capacity) {
        addEdge(tail, head, flow, capacity);
        addEdge(head, tail, 0, 0);
        vertex[tail].o += flow;
        vertex[head].i += flow;
        return;
    }

    bool BFS(int s, int t, int ver) {
        diq q;
        for (int i = 0; i <= n + m + 3; i++) vertex[i].cur = vertex[i].head;
        for (int i = 0; i <= n + m + 3; i++) vertex[i].dep = 0;
        vertex[s].dep = 1;
        q.push_back(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop_front();
            for (int e = vertex[u].head; ~e; e = edge[e].next) {
                int v = edge[e].head;
                int w = edge[e].capacity - edge[e].flow;
                if (w == 0) continue;
                if (e >= ver) continue;
                if (vertex[v].dep) continue;
                vertex[v].dep = vertex[u].dep + 1;
                q.push_back(v);
            }
        }
        return vertex[t].dep;
    }

    int DFS(int u, int t, int ver, int lim) {
        if (u == t) return lim;
        if (!lim) return lim;
        int ret = 0;
        for (int &e = vertex[u].cur; ~e; e = edge[e].next) {
            int v = edge[e].head;
            int w = edge[e].capacity - edge[e].flow;
            if (w == 0) continue;
            if (e >= ver) continue;
            if (vertex[v].dep != vertex[u].dep + 1) continue;
            int flow = DFS(v, t, ver, std::min(lim - ret, w));
            ret += flow;
            edge[e].flow += flow;
            edge[e ^ 1].flow -= flow;
            if (ret == lim) break;
        }
        return ret;
    }

    int Dinic(int s, int t, int ver) {
        int ret = 0;
        while (BFS(s, t, ver)) ret += DFS(s, t, ver, inf);
        return ret;
    }
}

void mian() {
    graph::init();
    s = 0;
    t = n + m + 1;
    S = n + m + 2;
    T = n + m + 3;
    for (int i = 1; i <= m; i++) std::cin >> g, graph::AddEdge(i + n, t, g, inf);
    for (int i = 1; i <= n; i++) {
        std::cin >> c >> d;
        graph::AddEdge(s, i, 0, d);
        for (int j = 1; j <= c; j++) {
            std::cin >> x >> l >> r;
            graph::AddEdge(i, n + x + 1, l, r);
        }
    }
    int ver = graph::ecnt;
    int sum = 0;
    graph::AddEdge(t, s, 0, inf);
    for (int i = 0; i <= n + m + 1; i++) {
        if (graph::vertex[i].i > graph::vertex[i].o) graph::AddEdge(S, i, 0, graph::vertex[i].i - graph::vertex[i].o), sum += graph::vertex[i].i - graph::vertex[i].o;
        if (graph::vertex[i].i < graph::vertex[i].o) graph::AddEdge(i, T, 0, graph::vertex[i].o - graph::vertex[i].i);
    }
    if (graph::Dinic(S, T, inf) != sum) {
        std::cout << -1 << '\n';
    } else {
        std::cout << graph::Dinic(s, t, ver) + graph::edge[ver].flow << '\n';
    }
    std::cout << '\n';
    return;
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) mian();
    return 0;
}