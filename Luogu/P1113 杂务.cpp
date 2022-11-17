#include <cstdio>
#include <algorithm>
#include <queue>

const int maxN = 1e4 + 10;
const int maxM = 1e8 + 10;

int n;
int task[maxN];
int len[maxN];

namespace Graph {
    struct Vertex {
        int head;
        int degree;
        int rank;
    };
    
    struct Edge {
        int head;
        int next;
    };

    Vertex vertex[maxN];
    Edge edge[maxM];
    int ecnt;

    void AddEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        vertex[head].degree++;
        return;
    }

    int ans;

    void TopoSort() {
        std::queue<int> waiting;
        for (int i = 1; i <= n; i++) if (!vertex[i].degree) {
            waiting.push(i);
            vertex[i].rank = len[i];
        }
        while (!waiting.empty()) {
            int u = waiting.front();
            waiting.pop();
            for (int i = vertex[u].head; i; i = edge[i].next) {
                int v = edge[i].head;
                vertex[v].degree--;
                if (!vertex[v].degree) waiting.push(v);
                vertex[v].rank = std::max(vertex[v].rank, vertex[u].rank + len[v]);
                ans = std::max(ans, vertex[v].rank);
            }
        }
        return;
    }
};

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &task[i], &len[i]);
        int list;
        while (scanf("%d", &list) && list) Graph::AddEdge(task[i], list);
    }
    Graph::TopoSort();
    printf("%d\n", Graph::ans);
    return 0;
}