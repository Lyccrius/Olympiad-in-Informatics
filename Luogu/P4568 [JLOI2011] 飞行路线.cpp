#include <cstdio>
#include <algorithm>
#include <queue>

const int inf = 0x3f3f3f3f;
const int maxN = 1e4 + 10;
const int maxM = 5e4 + 10;
const int maxK = 10;

int n, m, k;
int s, t;

namespace Flight {
    struct Vertex {
        int u;
        int cost;
        int head;
        bool relaxed;

        bool operator<(Vertex other) const {
            return cost > other.cost;
        }
    };

    struct Edge {
        int cost;
        int head;
        int next;
    };

    Vertex city[maxN * maxK * 10];
    Edge route[maxM * maxK * 20];
    int ecnt;

    void AddRoute(int from, int to, int cost) {
        ecnt++;
        route[ecnt].cost = cost;
        route[ecnt].head = to;
        route[ecnt].next = city[from].head;
        city[from].head = ecnt;
        city[from].cost = inf;
        city[to].cost = inf;
        city[from].u = from;
        city[to].u = to;
        return;
    }

    void Dijkstra() {
        std::priority_queue<Vertex> waiting;
        city[s].cost = 0;
        waiting.push(city[s]);
        while (!waiting.empty()) {
            int u = waiting.top().u;
            waiting.pop();
            if (city[u].relaxed) continue;
            city[u].relaxed = true;
            for (int i = city[u].head; i; i = route[i].next) {
                int v = route[i].head;
                int w = route[i].cost;
                if (city[v].cost > city[u].cost + w) {
                    city[v].cost = city[u].cost + w;
                    waiting.push(city[v]);
                }
            }
        }
        return;
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    scanf("%d%d", &s, &t);
    k = std::min(m, k);
    for (int i = 1; i <= m; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        Flight::AddRoute(a, b, c);
        Flight::AddRoute(b, a, c);
        for (int j = 1; j <= k; j++) {
            Flight::AddRoute(j * n + a, j * n + b, c);
            Flight::AddRoute(j * n + b, j * n + a, c);
            Flight::AddRoute((j - 1) * n + a, j * n + b, 0);
            Flight::AddRoute((j - 1) * n + b, j * n + a, 0);
        }
    }
    Flight::Dijkstra();
    printf("%d\n", Flight::city[k * n + t].cost);
    return 0;
}