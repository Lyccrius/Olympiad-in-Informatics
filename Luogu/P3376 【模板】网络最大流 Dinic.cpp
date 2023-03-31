#include <iostream>
#include <deque>

#define int long long

typedef std::deque<int> diq;

const int maxN = 200;
const int maxM = 5000;
const int inf = (1ll << 31) - 1;

int n, m, s, t;
int u, v, c;

namespace graph {
    struct Vertex {
        int head;
        int cur;
        int dep;

        Vertex() {
            head = -1;
            return;
        }
    } vertex[maxN + 10];
    
    struct Edge {
        int head;
        int next;
        int flow;
        int capacity;
    } edge[2 * maxM + 10];

    int ecnt;

    void addEdge(int tail, int head, int flow, int capacity) {
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        edge[ecnt].flow = flow;
        edge[ecnt].capacity = capacity;
        vertex[tail].head = ecnt;
        ecnt++;
        return;
    }

    bool BFS() {
        for (int u = 1; u <= n; u++) vertex[u].dep = 0;
        vertex[s].dep = 1;
        diq q;
        q.push_back(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop_front();
            for (int e = vertex[u].head; ~e; e = edge[e].next) {
                int v = edge[e].head;
                if (vertex[v].dep) continue;
                if (edge[e].capacity == edge[e].flow) continue;
                vertex[v].dep = vertex[u].dep + 1;
                q.push_back(v);
            }
        }
        return vertex[t].dep;
    }

    int DFS(int u, int maxf) {
        if (u == t) return maxf;
        if (!maxf) return 0;
        int ret = 0;
        for (int &e = vertex[u].cur; ~e; e = edge[e].next) {
            int v = edge[e].head;
            if (vertex[v].dep != vertex[u].dep + 1) continue;
            int flow = DFS(v, std::min(maxf - ret, edge[e].capacity - edge[e].flow));
            if (!flow) continue;
            ret += flow;
            edge[e].flow += flow;
            edge[e ^ 1].flow -= flow;
            if (ret == maxf) break;
        }
        return ret;
    }

    int Dinic() {
        int ret = 0;
        while (BFS()) {
            for (int u = 1; u <= n; u++) vertex[u].cur = vertex[u].head;
            ret += DFS(s, inf);
        }
        return ret;
    }
}

signed main() {
    std::cin >> n >> m >> s >> t;
    for (int i = 1; i <= m; i++) {
        std::cin >> u >> v >> c;
        graph::addEdge(u, v, 0, c);
        graph::addEdge(v, u, 0, 0);
    }
    std::cout << graph::Dinic();
    return 0;
}