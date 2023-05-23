#include <iostream>
#include <deque>

typedef std::deque<int> diq;
typedef std::pair<int, int> pii;

const int maxN = 200;
const int maxM = 200;
const int maxK = 10;
const int maxT = 3000;
const int maxf = 200;
const int maxg = 2000;
const int inf = 1e9;

int N, M, K, T;
int f[maxN + 10][maxN + 10];
int g[maxN + 10][maxN + 10];
int a[maxM + 10], b[maxM + 10], s[maxM + 10], t[maxM + 10], c[maxM + 10];

namespace graph {
    struct Vertex {
        int head;
        int vis;
        int dis;
        int cur;

        Vertex() {
            head = -1;
        }
    } vertex[2 * maxM + 10];

    struct Edge {
        int head;
        int next;
        int cost;
        int flow;
        int capacity;
    } edge[2 * (3 * maxM + maxM * maxM) + 10];

    int ecnt;

    void addEdge(int tail, int head, int cost, int capacity) {
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        edge[ecnt].cost = cost;
        edge[ecnt].capacity = capacity;
        vertex[tail].head = ecnt;
        ecnt++;
        return;
    }

    void AddEdge(int tail, int head, int cost, int capacity) {
        addEdge(tail, head, cost, capacity);
        addEdge(head, tail, - cost, 0);
        return;
    }

    bool SPFA(int s, int t) {
        diq q;
        for (int i = 0; i <= t; i++) vertex[i].dis = - maxg;
        for (int i = 0; i <= t; i++) vertex[i].vis = false;
        vertex[s].dis = 0;
        q.push_back(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop_front();
            vertex[u].vis = false;
            for (int e = vertex[u].head; ~e; e = edge[e].next) {
                int v = edge[e].head;
                int w = edge[e].cost;
                if (edge[e].flow == edge[e].capacity) continue;
                if (vertex[v].dis < vertex[u].dis + w) {
                    vertex[v].dis = vertex[u].dis + w;
                    if (vertex[v].vis == false) {
                        vertex[v].vis = true;
                        q.push_back(v);
                    }
                }
            }
        }
        return vertex[t].dis > - maxg;
    }

    pii DFS(int u, int t, int lim) {
        if (u == t) return std::make_pair(lim, 0);
        if (!lim) return std::make_pair(lim, 0);
        pii ret = std::make_pair(0, 0);
        vertex[u].vis = true;
        for (int &e = vertex[u].cur; ~e; e = edge[e].next) {
            int v = edge[e].head;
            int w = edge[e].cost;
            if (edge[e].flow == edge[e].capacity) continue;
            if (vertex[v].dis != vertex[u].dis + w) continue;
            if (vertex[v].vis) continue;
            pii flow = DFS(v, t, std::min(lim - ret.first, edge[e].capacity - edge[e].flow));
            ret.first += flow.first;
            ret.second += flow.second;
            ret.second += flow.first * w;
            edge[e].flow += flow.first;
            edge[e ^ 1].flow -= flow.first;
        }
        return ret;
    }

    pii Dinic(int s, int t) {
        pii ret = std::make_pair(0, 0);
        while (SPFA(s, t)) {
            for (int u = 0; u <= t; u++) vertex[u].cur = vertex[u].head;
            for (int u = 0; u <= t; u++) vertex[u].vis = false;
            pii flow = DFS(s, t, maxK);
            ret.first += flow.first;
            ret.second += flow.second;
        }
        return ret;
    }
}

int main() {
    std::cin >> N >> M >> K >> T;
    int ss = 0;
    int sp = 2 * M + 1;
    int tp = 2 * M + 2;
    for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++) std::cin >> f[i][j];
    for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++) std::cin >> g[i][j];
    for (int i = 1; i <= M; i++) std::cin >> a[i] >> b[i] >> s[i] >> t[i] >> c[i];
    for (int i = 1; i <= M; i++) a[i]++, b[i]++;
    for (int i = 1; i <= M; i++) graph::AddEdge(i, i + M, c[i], 1);
    for (int i = 1; i <= M; i++) for (int j = 1; j <= M; j++) if (i != j) if (s[j] - t[i] >= f[b[i]][a[j]]) graph::AddEdge(i + M, j, - g[b[i]][a[j]], 1);
    for (int i = 1; i <= M; i++) if (s[i] >= f[1][a[i]]) graph::AddEdge(sp, i, - g[1][a[i]], 1);
    for (int i = 1; i <= M; i++) if (t[i] + f[b[i]][1] <= T) graph::AddEdge(i + M, tp, - g[b[i]][1], 1);
    graph::AddEdge(ss, sp, 0, K);
    std::cout << graph::Dinic(ss, tp).second << '\n';
    return 0;
}