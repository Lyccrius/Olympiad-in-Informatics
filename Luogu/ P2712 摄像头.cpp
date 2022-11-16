#include <cstdio>
#include <algorithm>
#include <queue>

const int maxN = 500 + 10;
const int maxM = 10000 + 10;

int n, m;
bool camera[maxN];
int maxX;

namespace Graph {
    struct Vertex {
        int head;
        int degree;
    };

    struct Edge {
        int head;
        int next;
    };

    Vertex vertex[maxN];
    Edge edge[maxM * 2];
    int ecnt;

    void AddEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        vertex[head].degree++;
    }

    int topoRank[maxN];
    int tcnt;

    void TopoSort() {
        std::queue<int> waiting;
        for (int i = 1; i <= maxX; i++) if (vertex[i].degree == 0 && camera[i]) waiting.push(i);
        while (!waiting.empty()) {
            int u = waiting.front();
            waiting.pop();
            tcnt++;
            topoRank[tcnt] = u;
            for (int i = vertex[u].head; i; i = edge[i].next) {
                int v = edge[i].head;
                if (camera[v]) {
                    vertex[v].degree--;
                    if (vertex[v].degree == 0) waiting.push(v);
                }
            }
        }
        return;
    }
};

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int x, m;
        scanf("%d%d", &x, &m);
        maxX = std::max(maxX, x);
        camera[x] = true;
        for (int j = 1; j <= m; j++) {
            int v;
            scanf("%d", &v);
            Graph::AddEdge(x, v);
        }
    }
    Graph::TopoSort();
    int ans = n;
    for (int i = 1; i <= Graph::topoRank[i]; i++) if (camera[Graph::topoRank[i]]) ans--;
    if (ans) printf("%d\n", ans);
    else printf("YES\n");
    return 0;
}