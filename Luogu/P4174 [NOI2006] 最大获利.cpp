#include <iostream>
#include <deque>

typedef std::deque<int> diq;

const int maxN = 5000;
const int maxM = 50000;
const int maxC = 100;
const int maxP = 100;
const int inf = maxN * maxP + maxM * maxC;

int n, m;
int p[maxN + 10];
int a[maxM + 10], b[maxM + 10], c[maxM + 10];
int ans;

namespace graph {
    struct Vertex {
        int head;
        int dep;
        int cur;

        Vertex() {
            head = -1;
        }
    } vertex[maxN + maxM + 10];

    struct Edge {
        int head;
        int next;
        int flow;
        int capacity;
    } edge[2 * (maxN + 3 * maxM) + 10];

    int ecnt;

    void addEdge(int tail, int head, int capacity) {
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        edge[ecnt].capacity = capacity;
        vertex[tail].head = ecnt;
        ecnt++;
        return;
    }

    void AddEdge(int tail, int head, int capacity) {
        addEdge(tail, head, capacity);
        addEdge(head, tail, 0);
        return;
    }

    bool BFS(int s, int t) {
        diq q;
        for (int i = 0; i <= n + m + 1; i++) vertex[i].cur = vertex[i].head;
        for (int i = 0; i <= n + m + 1; i++) vertex[i].dep = 0;
        vertex[s].dep = 1;
        q.push_back(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop_front();
            for (int e = vertex[u].head; ~e; e = edge[e].next) {
                int v = edge[e].head;
                int w = edge[e].capacity - edge[e].flow;
                if (w == 0) continue;
                if (vertex[v].dep) continue;
                vertex[v].dep = vertex[u].dep + 1;
                q.push_back(v);
            }
        }
        return vertex[t].dep;
    }

    int DFS(int u, int t, int lim) {
        if (u == t) return lim;
        if (!lim) return lim;
        int ret = 0;
        for (int &e = vertex[u].cur; ~e; e = edge[e].next) {
            int v = edge[e].head;
            int w = edge[e].capacity - edge[e].flow;
            if (w == 0) continue;
            if (vertex[v].dep != vertex[u].dep + 1) continue;
            int flow = DFS(v, t, std::min(lim - ret, w));
            ret += flow;
            edge[e].flow += flow;
            edge[e ^ 1].flow -= flow;
            if (lim == ret) break;
        }
        return ret;
    }

    int Dinic(int s, int t) {
        int ret = 0;
        while (BFS(s, t)) ret += DFS(s, t, inf);
        return ret;
    }
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) std::cin >> p[i];
    for (int i = 1; i <= m; i++) std::cin >> a[i] >> b[i] >> c[i];
    for (int i = 1; i <= n; i++) graph::AddEdge(i, n + m + 1, p[i]);
    for (int i = 1; i <= m; i++) graph::AddEdge(0, n + i, c[i]);
    for (int i = 1; i <= m; i++) graph::AddEdge(n + i, a[i], inf);
    for (int i = 1; i <= m; i++) graph::AddEdge(n + i, b[i], inf);
    for (int i = 1; i <= m; i++) ans += c[i];
    std::cout << ans - graph::Dinic(0, n + m + 1) << '\n';
    return 0;
}