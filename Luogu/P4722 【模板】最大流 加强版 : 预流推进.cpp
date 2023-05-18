#include <iostream>
#include <algorithm>
#include <deque>

typedef std::deque<int> diq;

const int maxN = 1200;
const int maxM = 120000;
const int maxC = (1ll << 31) - 1;

int n, m, s, t;
int u, v, c;

namespace graph {
    struct Vertex {
        diq e;
        int dis;
        int cur;
    } vertex[maxN + 10];

    struct Edge {
        int tail;
        int head;
        int capacity;
        int flow;

        bool operator<(const Edge &other) const {
            return capacity > other.capacity;
        }
    } edge[2 * maxM + 10];

    int ecnt;

    void addEdge(int tail, int head, int capacity) {
        edge[ecnt].tail = tail;
        edge[ecnt].head = head;
        edge[ecnt].capacity = capacity;
        edge[ecnt].flow = 0;
        vertex[tail].e.push_back(ecnt);
        ecnt++;
        edge[ecnt].tail = head;
        edge[ecnt].head = tail;
        edge[ecnt].capacity = 0;
        edge[ecnt].flow = 0;
        ecnt++;
        return;
    }

    bool BFS(int s, int t) {
        diq q;
        for (int u = 1; u <= n; u++) vertex[u].dis = maxN;
        vertex[s].dis = 0;
        q.push_back(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop_front();
            for (auto e : vertex[u].e) {
                int v = edge[e].head;
                if (edge[e].flow == edge[e].capacity) continue;
                if (vertex[v].dis > vertex[u].dis + 1) {
                    vertex[v].dis = vertex[u].dis + 1;
                    q.push_back(v);
                }
            }
        }
        return vertex[t].dis < maxN;
    }

    int DFS(int u, int t, int tot) {
        if (u == t) return tot;
        if (!tot) return tot;
        int ret = 0;
        for (int &i = vertex[u].cur; i < vertex[u].e.size(); i++) {
            int e = vertex[u].e[i];
            int v = edge[e].head;
            if (vertex[v].dis != vertex[u].dis + 1) continue;
            int flow = DFS(v, t, std::min(tot - ret, edge[e].capacity - edge[e].flow));
            if (flow == 0) continue;
            ret += flow;
            edge[e].flow += flow;
            edge[e ^ 1].flow -= flow;
            if (tot == ret) break;
        }
        return ret;
    }

    int Dinic(int s, int t) {
        int flow = 0;
        while (BFS(s, t)) {
            for (int u = 1; u <= n; u++) vertex[u].cur = 0;
            flow += DFS(s, t, maxC);
        }
        return flow;
    }
}

std::deque<graph::Edge> e;
int ans = 0;

int main() {
    std::cin >> n >> m >> s >> t;
    for (int i = 1; i <= m; i++) std::cin >> u >> v >> c, e.push_back((graph::Edge) {u, v, c});
    std::sort(e.begin(), e.end());
    for (int rev = 0; rev <= 1; rev++) for (int lim = (1 << 30), i = 0; lim >= 1; lim = lim / 2) {
        while (i < e.size() && e[i].capacity >= lim) {
            if (rev) graph::vertex[e[i].head].e.push_back(i * 2 + 1);
            else graph::addEdge(e[i].tail, e[i].head, e[i].capacity);
            i++;
        }
        ans += graph::Dinic(s, t);
    }
    std::cout << ans << '\n';
    return 0;
}