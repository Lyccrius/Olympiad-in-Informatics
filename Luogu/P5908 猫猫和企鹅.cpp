#include <cstdio>
#include <algorithm>
#include <queue>

const int inf = 1e9 + 10;
const int maxN = 1e5 + 10;

int n, d;
int ans = 0;

namespace Kingdom {
    struct Vertex {
        int head;
        int dis;
        bool visited;
    };

    struct Edge {
        int head;
        int next;
    };

    Vertex area[maxN];
    Edge road[maxN * 2];
    int ecnt;

    void AddEdge(int tail, int head) {
        ecnt++;
        road[ecnt].head = head;
        road[ecnt].next = area[tail].head;
        area[tail].head = ecnt;
        area[tail].dis = inf;
        area[head].dis = inf;
        return;
    }

    std::queue<int> waiting;

    void BFS() {
        while (!waiting.empty()) {
            int u = waiting.front();
            waiting.pop();
            area[u].visited = true;
            if (area[u].dis <= d) ans++;
            else break;
            for (int i = area[u].head; i; i = road[i].next) {
                int v = road[i].head;
                if (area[v].visited) continue;
                area[v].dis = area[u].dis + 1;
                waiting.push(v);
            }
        }
        return;
    }
}

int main() {
    scanf("%d%d", &n, &d);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        Kingdom::AddEdge(u, v);
        Kingdom::AddEdge(v, u);
    }
    Kingdom::area[1].dis = 0;
    Kingdom::waiting.push(1);
    Kingdom::BFS();
    printf("%d\n", ans - 1);
    return 0;
}