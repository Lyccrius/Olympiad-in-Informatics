#include <iostream>
#include <deque>

typedef long long lxl;
typedef std::deque<int> diq;

const int maxN = 100;
const int maxM = 600;
const int inf = 1e9 + 10;

int n, m, c1, c2;
int u, v;

namespace graph {
    struct Vertex {
        int head;
        int dis;
        int cur;

        Vertex() {
            head = -1;
            return;
        }
    } vertex[2 * maxN + 10];

    struct Edge {
        int head;
        int next;
        lxl flow;
        lxl capacity;
    } edge[2 * (2 * maxM + maxN) + 10];

    int ecnt;

    void addEdge(int tail, int head, lxl capcacity) {
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        edge[ecnt].capacity = capcacity;
        vertex[tail].head = ecnt;
        ecnt++;
        edge[ecnt].head = tail;
        edge[ecnt].next = vertex[head].head;
        edge[ecnt].capacity = 0;
        vertex[head].head = ecnt;
        ecnt++;
        return;
    }

    bool BFS(int s, int t) {
        diq q;
        for (int u = 1; u <= 2 * n; u++) vertex[u].dis = inf;
        vertex[s].dis = 0;
        q.push_back(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop_front();
            for (int e = vertex[u].head; ~e; e = edge[e].next) {
                int v = edge[e].head;
                if (edge[e].capacity == edge[e].flow) continue;
                if (vertex[v].dis > vertex[u].dis + 1) {
                    vertex[v].dis = vertex[u].dis + 1;
                    q.push_back(v);
                }
            }
        }
        return vertex[t].dis < maxN;
    }

    lxl DFS(int u, int t, lxl lim) {
        if (u == t) return lim;
        if (!lim) return lim;
        lxl ret = 0;
        for (int &e = vertex[u].cur; ~e; e = edge[e].next) {
            int v = edge[e].head;
            lxl w = edge[e].capacity - edge[e].flow;
            if (vertex[v].dis != vertex[u].dis + 1) continue;
            lxl flow = DFS(v, t, std::min(lim - ret, w));
            ret += flow;
            edge[e].flow += flow;
            edge[e ^ 1].flow -= flow;
            if (ret == lim) break;
        }
        return ret;
    }

    lxl Dinic(int s, int t) {
        lxl ret = 0;
        while (BFS(s, t)) {
            for (int u = 1; u <= 2 * n; u++) vertex[u].cur = vertex[u].head;
            ret += DFS(s, t, inf);
        }
        return ret;
    }
}

int main() {
    std::cin >> n >> m >> c1 >> c2;
    for (int i = 1; i <= n; i++) graph::addEdge(i, i + n, 1);
    for (int i = 1; i <= m; i++) std::cin >> u >> v, graph::addEdge(u + n, v, inf), graph::addEdge(v + n, u, inf);
    std::cout << graph::Dinic(c1 + n, c2) << '\n';
    return 0;
}