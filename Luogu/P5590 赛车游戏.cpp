#include <iostream>
#include <deque>

typedef std::deque<int> diq;

const int maxN = 1000;
const int maxM = 2000;
const int inf = 1e9 + 10;

int n, m;
int u[maxM + 10], v[maxM + 10], w[maxM + 10];

struct Graph {
    struct Vertex {
        int head;
        int next;
        int lead;
        int vis;
        int dis;
        int cnt;

        Vertex() {
            head = -1;
            dis = inf;
            return;
        }
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
        int weight;
    } edge[2 * maxM + 10];

    int ecnt;

    void addEdge(int tail, int head, int weight) {
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        edge[ecnt].weight = weight;
        vertex[tail].head = ecnt;
        ecnt++;
        return;
    }

    void DFS(int u) {
        if (vertex[u].vis) return;
        vertex[u].vis = true;
        if (u == n) vertex[u].lead = true;
        for (int e = vertex[u].head; ~e; e = edge[e].next) {
            int v = edge[e].head;
            DFS(v);
            vertex[u].lead |= vertex[v].lead;
        }
        return;
    }

    bool SPFA() {
        diq q;
        q.push_back(1);
        vertex[1].dis = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop_front();
            vertex[u].vis = false;
            for (int e = vertex[u].head; ~e; e = edge[e].next) {
                int v = edge[e].head;
                int w = edge[e].weight;
                if (vertex[v].dis > vertex[u].dis + w) {
                    vertex[v].dis = vertex[u].dis + w;
                    vertex[v].cnt = vertex[u].cnt + 1;
                    if (vertex[v].cnt > n) return false;
                    if (vertex[v].vis == false) q.push_back(v);
                    vertex[v].vis = true;
                }
            }
        }
        return true;
    }
} full, part;

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        std::cin >> u[i] >> v[i];
        full.addEdge(u[i], v[i], 0);
    }
    full.DFS(1);
    for (int i = 1; i <= m; i++) {
        if (full.vertex[u[i]].lead && full.vertex[v[i]].lead) {
            part.addEdge(u[i], v[i], 9);
            part.addEdge(v[i], u[i], -1);
        }
    }
    if (!full.vertex[1].lead || !part.SPFA()) {
        std::cout << -1 << '\n';
        return 0;
    }
    std::cout << n << ' ' << m << '\n';
    for (int i = 1; i <= m; i++) {
        w[i] = part.vertex[v[i]].dis - part.vertex[u[i]].dis;
        if (!full.vertex[u[i]].lead || !full.vertex[v[i]].lead) w[i] = 1;
        std::cout << u[i] << ' ' << v[i] << ' ' << w[i] << '\n';
    }
    return 0;
}