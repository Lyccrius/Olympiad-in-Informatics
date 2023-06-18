#include <iostream>
#include <iomanip>
#include <deque>
#include <cmath>

typedef double dbl;
typedef std::deque<int> diq;

const int maxN = 400;
const dbl eps = 1e-6;
const dbl inf = 1e10;

int n;
int x[maxN + 10], y[maxN + 10];
int s, t;

dbl dis(int i, int j) {
    return sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
}

namespace graph {
    struct Vertex {
        int head;
        int inq;
        int vis;
        dbl dis;
        int cur;

        Vertex() {
            head = -1;
            return;
        }
    } vertex[2 * maxN + 10];

    struct Edge {
        int head;
        int next;
        dbl cost;
        int flow;
        int capacity;
    } edge[2 * (maxN + maxN + maxN * maxN) + 10];

    int ecnt;
    int flow;
    dbl cost;

    void addedge(int tail, int head, dbl cost, int capacity) {
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        edge[ecnt].cost = cost;
        edge[ecnt].capacity = capacity;
        vertex[tail].head = ecnt;
        ecnt++;
        return;
    }

    void addEdge(int tail, int head, dbl cost, int capacity) {
        addedge(tail, head, cost, capacity);
        addedge(head, tail, - cost, 0);
        return;
    }

    bool BFS() {
        diq q;
        for (int i = s; i <= t; i++) vertex[i].inq = false;
        for (int i = s; i <= t; i++) vertex[i].vis = false;
        for (int i = s; i <= t; i++) vertex[i].dis = inf;
        for (int i = s; i <= t; i++) vertex[i].cur = vertex[i].head;
        vertex[s].dis = 0;
        q.push_back(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop_front();
            vertex[u].inq = false;
            for (int e = vertex[u].head; ~e; e = edge[e].next) {
                int v = edge[e].head;
                dbl w = edge[e].cost;
                if (edge[e].flow == edge[e].capacity) continue;
                if (vertex[v].dis > vertex[u].dis + w) {
                    vertex[v].dis = vertex[u].dis + w;
                    if (vertex[v].inq == false) {
                        vertex[v].inq = true;
                        q.push_back(v);
                    }
                }
            }
        }
        return vertex[t].dis < inf;
    }

    int DFS(int u, int lim) {
        if (u == t) return lim;
        if (!lim) return lim;
        int ret = 0;
        vertex[u].vis = true;
        for (int &e = vertex[u].cur; ~e; e = edge[e].next) {
            int v = edge[e].head;
            dbl w = edge[e].cost;
            if (vertex[v].vis) continue;
            if (edge[e].flow == edge[e].capacity) continue;
            if (std::abs(vertex[v].dis - (vertex[u].dis + w)) >= eps) continue;
            int flow = DFS(v, std::min(lim, edge[e].capacity - edge[e].flow));
            cost += flow * w;
            ret += flow;
            lim -= flow;
            edge[e].flow += flow;
            edge[e ^ 1].flow -= flow;
        }
        vertex[u].vis = false;
        return ret;
    }

    void Dinic() {
        while (BFS()) flow += DFS(s, inf);
        return;
    }
}

int main() {
    std::cin >> n;
    s = 0;
    t = 2 * n + 1;
    for (int i = 1; i <= n; i++) std::cin >> x[i] >> y[i];
    for (int i = 1; i <= n; i++) graph::addEdge(s, i, 0, 1);
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) if (y[i] < y[j]) graph::addEdge(i, j + n, dis(i, j), 1);
    for (int i = 1; i <= n; i++) graph::addEdge(i + n, t, 0, 2);
    graph::Dinic();
    if (graph::flow != n - 1) graph::cost = -1;
    std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(7) << graph::cost << '\n';
    return 0;
}