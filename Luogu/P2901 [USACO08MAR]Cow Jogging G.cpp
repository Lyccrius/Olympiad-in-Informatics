#include <iostream>
#include <vector>
#include <deque>
#include <queue>

typedef std::vector<int> vic;
typedef std::deque<int> diq;

const int maxN = 1000;
const int maxM = 1e4;
const int maxK = 100;
const int inf = 1e9;

int n, m, k;
int u, v, w;
int h[maxN + 10];

struct Graph {
    struct Vertex {
        int head;
        int vis;
        int dis;
        int cnt;
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
        int weight;
    } edge[maxM + 10];

    int ecnt;

    void addEdge(int tail, int head, int weight) {
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
        int dis;
        vic path;

        bool operator<(const Node &other) const {
            if (dis + h[u] != other.dis + h[other.u]) return dis + h[u] > other.dis + h[other.u];
            for (int i = 0; i < std::min(path.size(), other.path.size()); i++) {
                if (path[i] != other.path[i]) return path[i] > other.path[i];
            }
            return path.size() > other.path.size();
        }
    };

    void Astar(int k, int s, int t) {
        std::priority_queue<Node> q;
        vic p;
        p.push_back(s);
        q.push((Node) {s, 0, p});
        while (!q.empty()) {
            int u = q.top().u;
            int dis = q.top().dis;
            vic path = q.top().path;
            q.pop();
            vertex[u].cnt++;
            if (vertex[u].cnt > k) continue;
            if (u == t) {
                std::cout << dis << '\n';
            }
            for (int e = vertex[u].head; e; e = edge[e].next) {
                int v = edge[e].head;
                int w = edge[e].weight;
                vic t = path;
                int ok = true;
                for (auto i : t) if (i == v) ok = false;
                if (!ok) continue;
                t.push_back(v);
                q.push((Node) {v, dis + w, t});
            }
        }
        for (int i = vertex[t].cnt + 1; i <= k; i++) std::cout << -1 << '\n';
        return;
    }
} f, r;

int main() {
    std::cin >> n >> m >> k;
    for (int i = 1; i <= m; i++) std::cin >> u >> v >> w, f.addEdge(u, v,  w), r.addEdge(v, u, w);
    r.SPFA(1);
    for (int i = 1; i <= n; i++) h[i] = r.vertex[i].dis;
    f.Astar(k, n, 1);
    return 0;
}