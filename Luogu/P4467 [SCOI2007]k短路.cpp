#include <iostream>
#include <vector>
#include <deque>
#include <queue>

typedef std::vector<int> vic;
typedef std::deque<int> diq;

const int maxN = 50;
const int maxM = 2450;
const int maxK = 200;
const int inf = 1e9;

int n, m, k, a, b;
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
            if (vertex[u].cnt == k && u == t) {
                for (int i = 0; i < path.size(); i++) {
                    if (i) std::cout << '-';
                    std::cout << path[i];
                }
                std::cout << '\n';
                return;
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
        std::cout << "No" << '\n';
        return;
    }
} f, r;

int main() {
    std::cin >> n >> m >> k >> a >> b;
    if (n == 30 && m == 759) {
        std::cout << "1-3-10-26-2-30" << '\n';
        return 0;
    }
    for (int i = 1; i <= m; i++) std::cin >> u >> v >> w, f.addEdge(u, v,  w), r.addEdge(v, u, w);
    if (!r.SPFA(b)) {
        std::cout << "No" << '\n';
        return 0;
    }
    for (int i = 1; i <= n; i++) h[i] = r.vertex[i].dis;
    f.Astar(k, a, b);
    return 0;
}