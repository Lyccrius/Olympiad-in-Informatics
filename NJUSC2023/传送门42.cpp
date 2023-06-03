#include <iostream>
#include <vector>
#include <set>
#include <queue>

typedef bool bol;
typedef long long lxl;
typedef std::set<int> sit;

const int maxN = 500;
const int maxK = 1e6;
const lxl inf = 1e18;

int n, k;
int v[maxK + 10];
lxl a[maxN + 10][maxN + 10];
lxl b[maxN + 10][maxN + 10];
sit tar[maxN + 10];
lxl res;
lxl ans = inf;

namespace graph {
    struct Vertex {
        int id;
        bol vis;
        lxl dis;
        sit target;

        bool operator<(const Vertex &other) const {
            return dis > other.dis;
        }
    } vertex[maxN + 10];

    void Dijkstra(int s) {
        for (int i = 1; i <= n; i++) vertex[i].id = i;
        for (int i = 1; i <= n; i++) vertex[i].vis = false;
        for (int i = 1; i <= n; i++) vertex[i].dis = inf;
        vertex[s].target = tar[s];
        vertex[s].dis = 0;
        std::priority_queue<Vertex> q;
        q.push(vertex[s]);
        while (!q.empty() && !vertex[s].target.empty()) {
            int u = q.top().id;
            q.pop();
            if (vertex[u].vis) continue;
            vertex[u].vis = true;
            if (vertex[s].target.find(u) != vertex[s].target.end()) {
                vertex[s].target.erase(u);
                res += vertex[u].dis;
                //printf("%d to %d: %d\n", s, u, vertex[u].dis);
            }
            for (int v = 1; v <= n; v++) {
                if (vertex[v].dis > vertex[u].dis + b[u][v]) {
                    vertex[v].dis = vertex[u].dis + b[u][v];
                    q.push(vertex[v]);
                }
            }
        }
        return;
    }
}

int main() {
    std::cin >> n >> k;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) std::cin >> a[i][j];
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) b[i][j] = a[i][j];
    for (int i = 1; i <= k; i++) std::cin >> v[i];
    for (int i = 2; i <= k; i++) tar[v[i - 1]].insert(v[i]);
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            b[i][j] = 0;
            b[j][i] = 0;
            res = 0;
            for (int k = 1; k <= n; k++) graph::Dijkstra(k);
            ans = std::min(ans, res);
            b[i][j] = a[i][j];
            b[j][i] = a[j][i];
        }
    }
    std::cout << ans << '\n';
    return 0;
}