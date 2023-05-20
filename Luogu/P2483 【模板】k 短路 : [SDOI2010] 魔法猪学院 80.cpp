#include <iostream>
#include <deque>
#include <queue>

typedef std::deque<int> diq;
typedef double dbl;

const int maxN = 5000;
const int maxM = 2e5;
const int maxK = 100;
const int inf = 1e9;
const dbl eps = 1e-6;

int n, m; dbl e;
int u, v; dbl w;
dbl h[maxN + 10];

struct Graph {
    struct Vertex {
        int head;
        int vis;
        dbl dis;
        int cnt;
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
        dbl weight;
    } edge[maxM + 10];

    int ecnt;

    void addEdge(int tail, int head, dbl weight) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        edge[ecnt].weight = weight;
        vertex[tail].head = ecnt;
        return;
    }

    bool SPFA(int s) {
        diq q;
        for (int u = 1; u <= n; u++) vertex[u].dis = inf;
        vertex[s].dis = 0;
        q.push_back(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop_front();
            vertex[u].vis = false;
            for (int e = vertex[u].head; e; e = edge[e].next) {
                int v = edge[e].head;
                int w = edge[e].weight;
                if (vertex[v].dis > vertex[u].dis + w) {
                    vertex[v].dis = vertex[u].dis + w;
                    vertex[v].cnt = vertex[u].cnt + 1;
                    if (vertex[v].cnt >= n) return false;
                    if (vertex[v].vis == false) {
                        vertex[v].vis = true;
                        q.push_back(v);
                    }
                }
            }
        }
        return true;
    }

    struct Node {
        int u;
        dbl dis;

        bool operator<(const Node &other) const {
            return dis + h[u] > other.dis + h[other.u];
        }
    };

    void Astar(dbl e, int s, int t) {
        std::priority_queue<Node> q;
        q.push((Node) {s, 0});
        while (!q.empty()) {
            int u = q.top().u;
            dbl dis = q.top().dis;
            q.pop();
            if (dis - e > eps) break;
            vertex[u].cnt++;
            if (u == t) {
                e -= dis;
                continue;
            }
            for (int e = vertex[u].head; e; e = edge[e].next) {
                int v = edge[e].head;
                dbl w = edge[e].weight;
                q.push((Node) {v, dis + w});
            }
        }
        std::cout << vertex[t].cnt << '\n';
        return;
    }
} f, r;

int main() {
    std::cin >> n >> m >> e;
    for (int i = 1; i <= m; i++) {
        std::cin >> u >> v >> w;
        if (u == n) continue;
        f.addEdge(u, v,  w);
        r.addEdge(v, u, w);
    }
    r.SPFA(n);
    for (int i = 1; i <= n; i++) h[i] = r.vertex[i].dis;
    f.Astar(e, 1, n);
    return 0;
}