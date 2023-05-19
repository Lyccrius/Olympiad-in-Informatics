#include <iostream>
#include <deque>

typedef std::deque<int> diq;

const int maxN = 100;
const int maxM = 100;
const int maxA = 1e5;
const int inf = 1e9;
const int dx[5] = {0, 0, 1, 0, -1};
const int dy[5] = {0, 1, 0, -1, 0};

int n, m;
int a[maxN + 10][maxM + 10];
int s;

namespace graph {
    struct Vertex {
        int head;
        int dis;
        int cur;

        Vertex() {
            head = -1;
            return;
        }
    } vertex[maxN * maxM + 10];

    struct Edge {
        int head;
        int next;
        int flow;
        int capacity;
    } edge[2 * (maxN * maxM + maxN * maxM * 4) + 10];

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
        for (int u = 0; u <= n * m + 1; u++) vertex[u].dis = inf;
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
            for (int u = 0; u <= n * m + 1; u++) vertex[u].cur = vertex[u].head;
            ret += DFS(s, t, inf);
        }
        return ret;
    }
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) std::cin >> a[i][j];
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) s += a[i][j];
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) if ((i ^ j) & 1) graph::addEdge(0, (i - 1) * m + j, a[i][j]); else graph::addEdge((i - 1) * m + j, n * m + 1, a[i][j]);
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) if ((i ^ j) & 1) for (int k = 1; k <= 4; k++) if (1 <= i + dx[k] && i + dx[k] <= n) if (1 <= j + dy[k] && j + dy[k] <= m) graph::addEdge((i - 1) * m + j, (i + dx[k] - 1) * m + j + dy[k], inf);
    std::cout << s - graph::Dinic(0, n * m + 1);
    return 0;
}