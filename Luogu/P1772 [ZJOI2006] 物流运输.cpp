#include <iostream>
#include <deque>

typedef long long lxl;
typedef std::deque<int> diq;

const int maxN = 100;
const int maxM = 20;
const int maxK = 500;
const int maxE = 200;
const int inf = 1e9 + 10;

int n, m, k, e;
int u, v, w;
int d;
int p, a, b;

namespace graph {
    struct Vertex {
        int head;
        int vis;
        int dis;
        int ban;
    } vertex[maxM + 10];
    
    struct Edge {
        int head;
        int next;
        int weight;
    } edge[2 * maxE + 10];

    int ecnt;

    void addEdge(int tail, int head, int weight) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        edge[ecnt].weight = weight;
        vertex[tail].head = ecnt;
        return;
    }

    void SPFA(int s) {
        for (int i = 1; i <= m; i++) vertex[i].dis = inf;
        for (int i = 1; i <= m; i++) vertex[i].vis = false;
        diq q;
        q.push_back(s);
        vertex[s].dis = 0;
        if (vertex[s].ban) return;
        while (!q.empty()) {
            int u = q.front();
            q.pop_front();
            if (vertex[u].vis) continue;
            vertex[u].vis = true;
            for (int e = vertex[u].head; e; e = edge[e].next) {
                int v = edge[e].head;
                int w = edge[e].weight;
                if (vertex[v].ban) continue;
                if (vertex[v].dis > vertex[u].dis + w) {
                    vertex[v].dis = vertex[u].dis + w;
                    vertex[v].vis = false;
                    q.push_back(v);
                }
            }
        }
        return;
    }
}

int ban[maxN + 10][maxM + 10];
lxl cost[maxN + 10][maxN + 10];
lxl f[maxN + 10];

int main() {
    std::cin >> n >> m >> k >> e;
    for (int i = 1; i <= e; i++) {
        std::cin >> u >> v >> w;
        graph::addEdge(u, v, w);
        graph::addEdge(v, u, w);
    }
    std::cin >> d;
    for (int i = 1; i <= d; i++) {
        std::cin >> p >> a >> b;
        for (int j = a; j <= b; j++) {
            ban[j][p] = true;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            for (int u = 1; u <= m; u++) graph::vertex[u].ban = false;
            for (int k = i; k <= j; k++) {
                for (int u = 1; u <= m; u++) {
                    if (ban[k][u]) {
                        graph::vertex[u].ban = true;
                        //printf("ban %d\n", u);
                    }
                }
            }
            graph::SPFA(1);
            cost[i][j] = graph::vertex[m].dis;
            //printf("cost[%d][%d] = %d\n", i, j, cost[i][j]);
        }
    }
    for (int i = 1; i <= n; i++) {
        f[i] = cost[1][i] * i;
        for (int j = 1; j < i; j++) {
            f[i] = std::min(f[i], f[j] + cost[j + 1][i] * (i - j) + k);
        }
    }
    std::cout << f[n] << '\n';
    return 0;
}