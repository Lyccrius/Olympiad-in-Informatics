#include <cstdio>
#include <algorithm>

const int maxN = 1e4 + 10;
const int maxM = 1e5 + 10;

int n, m;

namespace College {
    struct Vertex {
        int head;
        bool visited;
        bool crab;
    };

    struct Edge {
        int head;
        int next;
    };

    Vertex vertex[maxN];
    Edge edge[maxN * 2];
    int ecnt;
    int ccnt[2];

    void AddEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    bool DFS(int u, int crab) {
        if (vertex[u].visited) {
            if (vertex[u].crab == crab) return true;
            return false;
        }
        vertex[u].visited = true;
        vertex[u].crab = crab;
        ccnt[crab]++;
        for (int i = vertex[u].head; i; i = edge[i].next) {
            int v = edge[i].head;
            if (!DFS(v, !crab)) return false;
        }
        return true;
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        College::AddEdge(u, v);
        College::AddEdge(v, u);
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (College::vertex[i].visited) continue;
        College::ccnt[0] = 0;
        College::ccnt[1] = 0;
        if (!College::DFS(i, 0)) {
            printf("Impossible\n");
            return 0;
        }
        ans += std::min(College::ccnt[0], College::ccnt[1]);
    }
    printf("%d\n", ans);
    return 0;
}