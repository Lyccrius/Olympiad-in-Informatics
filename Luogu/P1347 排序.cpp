#include <cstdio>
#include <algorithm>
#include <queue>

const int maxN = 26 + 10;
const int maxM = 600 + 10;

int n, m;

namespace Graph {
    struct Vertex {
        int head;
        int degree;
        int rank;
        bool scanned;
        bool sorted;
        int depth;
    };

    struct Edge {
        int head;
        int next;
    };

    Vertex vertex[maxN];
    int vcnt;
    Edge edge[maxM];
    int ecnt;

    void AddEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        vertex[head].degree++;
        if (!vertex[tail].scanned) vcnt++;
        if (!vertex[head].scanned) vcnt++;
        vertex[tail].scanned = true;
        vertex[head].scanned = true;
        vertex[tail].depth = 1;
        vertex[head].depth = 1;
        return;
    }

    int backUpDegree[maxN];

    void Init() {
        for (int i = 1; i <= n; i++) vertex[i].degree = backUpDegree[i];
        return;
    }

    void BackUp() {
        for (int i = 1; i <= n; i++) backUpDegree[i] = vertex[i].degree;
        return;
    }

    int tcnt;

    void TopoSort() {
        tcnt++;
        int rcnt = 0;
        int sorted[maxN];
        int deepest = 0;
        std::queue<int> waiting;
        for (int i = 1; i <= n; i++) if (vertex[i].scanned && !vertex[i].degree) waiting.push(i);
        while (!waiting.empty()) {
            int u = waiting.front();
            waiting.pop();
            rcnt++;
            sorted[rcnt] = u;
            for (int i = vertex[u].head; i; i = edge[i].next) {
                int v = edge[i].head;
                vertex[v].degree--;
                if (!vertex[v].degree) {
                    waiting.push(v);
                    vertex[v].depth = vertex[u].depth + 1;
                    deepest = std::max(deepest, vertex[v].depth);
                }
            }
        }
        if (deepest == n) {
            printf("Sorted sequence determined after %d relations: ",tcnt);
            for (int i = 1; i <= rcnt; i++) printf("%c", sorted[i] + 'A' - 1);
            printf(".");
            exit(0);
        }
        if (rcnt != vcnt) {
            printf("Inconsistency found after %d relations.", tcnt);
            exit(0);
        }
    }
};

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        Graph::Init();
        char x, y;
        int u, v;
        scanf(" %c<%c", &x, &y);
        u = x - 'A' + 1;
        v = y - 'A' + 1;
        Graph::AddEdge(u, v);
        Graph::BackUp();
        Graph::TopoSort();
    }
    printf("Sorted sequence cannot be determined.\n");
    return 0;
}