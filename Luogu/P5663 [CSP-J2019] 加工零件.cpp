#include <cstdio>
#include <queue>

const int maxN = 1e5 + 10;
const int maxM = 1e5 + 10;
const int inf = 1e9 + 10;

int n, m, q;
int u, v;
int a, L;

namespace Graph {
    struct Vertex {
        int head;
        int dis0;
        int dis1;
    } vertex[maxN];
    
    struct Edge {
        int head;
        int next;
    } edge[maxM << 1];
    int ecnt;

    void AddEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    void BFS(int s) {
        for (int i = 1; i <= n; i++) vertex[i].dis0 = inf, vertex[i].dis1 = inf;
        std::queue<int> waiting;
        waiting.push(s);
        vertex[s].dis0 = 0;
        while (!waiting.empty()) {
            int u = waiting.front();
            waiting.pop();
            for (int e = vertex[u].head; e; e = edge[e].next) {
                int v = edge[e].head;
                if (vertex[v].dis0 > vertex[u].dis1 + 1) {
                    vertex[v].dis0 = vertex[u].dis1 + 1;
                    waiting.push(v);
                }
                if (vertex[v].dis1 > vertex[u].dis0 + 1) {
                    vertex[v].dis1 = vertex[u].dis0 + 1;
                    waiting.push(v);
                }
            }
        }
        return;
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= m; i++) scanf("%d%d", &u, &v), Graph::AddEdge(u, v), Graph::AddEdge(v, u);
    Graph::BFS(1);
    while (q--) {
        scanf("%d%d", &a, &L);
        if (L % 2) {
            if (Graph::vertex[a].dis1 <= L) printf("Yes\n");
            else printf("No\n");
        } else {
            if (Graph::vertex[a].dis0 <= L) printf("Yes\n");
            else printf("No\n");
        }
    }
    return 0;
}