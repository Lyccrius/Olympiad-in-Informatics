#include <iostream>
#include <deque>

typedef std::deque<int> diq;

const int maxN = 500;
const int inf = 1e9 + 10;

int n;
int x[maxN + 10];
int f[maxN + 10];
int s;
int c;

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
        int flow;
        int capacity;
    } edge[2 * (maxN + maxN * maxN + 2 + 2) + 10];

    int ecnt;

    void addEdge(int tail, int head, int capcacity) {
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
        for (int u = 0; u <= 2 * n + 1; u++) vertex[u].dis = inf;
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
        return vertex[t].dis < inf;
    }

    int DFS(int u, int t, int lim) {
        if (u == t) return lim;
        if (!lim) return lim;
        int ret = 0;
        for (int &e = vertex[u].cur; ~e; e = edge[e].next) {
            int v = edge[e].head;
            int w = edge[e].capacity - edge[e].flow;
            if (vertex[v].dis != vertex[u].dis + 1) continue;
            int flow = DFS(v, t, std::min(lim - ret, w));
            ret += flow;
            edge[e].flow += flow;
            edge[e ^ 1].flow -= flow;
            if (ret == lim) break;
        }
        return ret;
    }

    int Dinic(int s, int t) {
        int ret = 0;
        while (BFS(s, t)) {
            for (int u = 0; u <= 2 * n + 1; u++) vertex[u].cur = vertex[u].head;
            ret += DFS(s, t, inf);
        }
        return ret;
    }
}

int main() {
    std::cin >> n;
    if (n == 1) {
        std::cout << 1 << '\n';
        std::cout << 1 << '\n';
        std::cout << 1 << '\n';
        return 0;
    }
    for (int i = 1; i <= n; i++) std::cin >> x[i];
    for (int i = 1; i <= n; i++) f[i] = 1;
    for (int i = 1; i <= n; i++) for (int j = 1; j < i; j++) if (x[j] <= x[i]) f[i] = std::max(f[i], f[j] + 1);
    for (int i = 1; i <= n; i++) s = std::max(s, f[i]);
    std::cout << s << '\n';
    for (int i = 1; i <= n; i++) graph::addEdge(i, i + n, 1);
    for (int i = 1; i <= n; i++) if (f[i] == 1) graph::addEdge(0, i, 1);
    for (int i = 1; i <= n; i++) if (f[i] == s) graph::addEdge(i + n, 2 * n + 1, 1);
    for (int i = 1; i <= n; i++) for (int j = 1; j < i; j++) if (x[j] <= x[i] && f[i] == f[j] + 1) graph::addEdge(j + n, i, 1);
    c += graph::Dinic(0, 2 * n + 1);
    std::cout << c << '\n';
    graph::addEdge(0, 1, inf);
    graph::addEdge(1, 1 + n, inf);
    if (f[n] == s) {
        graph::addEdge(n, n + n, inf);
        graph::addEdge(n + n, 2 * n + 1, inf);
    }
    c += graph::Dinic(0, 2 * n + 1);
    std::cout << c << '\n';
    return 0;
}