#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

const int maxN = 1000 + 10;
const int maxM = 1000 + 10;

int n, m;
int s;

namespace Station {
    struct Vertex {
        int head;
        int degree;
        int level;
        int added[maxN];
    };

    struct Edge {
        int head;
        int next;
    };

    Vertex vertex[maxN];
    Edge edge[maxN * maxN * 10];
    int ecnt;

    void AddEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        vertex[head].degree++;
        vertex[tail].level = 1;
        vertex[head].level = 1;
        vertex[tail].added[head] = 1;
        return;
    }

    int maxLevel;

    void TopoSort() {
        std::queue<int> waiting;
        for (int i = 1; i <= n; i++) if (!vertex[i].degree) waiting.push(i);
        while (!waiting.empty()) {
            int u = waiting.front();
            waiting.pop();
            for (int i = vertex[u].head; i; i = edge[i].next) {
                int v = edge[i].head;
                vertex[v].level = vertex[u].level + 1;
                maxLevel = std::max(maxLevel, vertex[v].level);
                vertex[v].degree--;
                if (!vertex[v].degree) waiting.push(v);
            }
        }
        return;
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d", &s);
        int stop[maxN];
        int stat[maxN];
        std::memset(stat, 0, sizeof(stat));
        for (int j = 1; j <= s; j++) {
            scanf("%d", &stop[j]);
            stat[stop[j]] = 1;
        }
        for (int j = stop[1]; j <= stop[s]; j++) if (!stat[j]) {
            for (int k = stop[1]; k <= stop[s]; k++) {
                if (stat[k]) if (!Station::vertex[j].added[k]) Station::AddEdge(j, k);
            }
        }
    }
    Station::TopoSort();
    printf("%d\n", Station::maxLevel);
    return 0;
}