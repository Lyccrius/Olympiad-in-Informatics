#include <cstdio>
#include <queue>

const int maxN = 2e5;

int n, k;
int u, v;

std::priority_queue<int> q;
long long ans;

namespace Graph {
    struct Vertex {
        int u;
        int head;
        int dep;
        int size;
        bool envoy;

        bool operator<(const Vertex &other) const {
            if (size != other.size) return size > other.size;
            return dep < other.dep;
        }
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
    } edge[maxN * 2 + 10];

    int ecnt;

    void AddEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    void DFS(int u, int from) {
        vertex[u].dep = vertex[from].dep + 1;
        vertex[u].size = 1;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            DFS(v, u);
            vertex[u].size += vertex[v].size;
        }
        q.push(vertex[u].dep - vertex[u].size);
        return;
    }

    void DFS2(int u, int from) {
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            if (vertex[v].envoy) ans += vertex[u].dep * vertex[v].size;
            else DFS2(v, u);
        }
        return;
    }
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i < n; i++) scanf("%d%d", &u, &v), Graph::AddEdge(u, v), Graph::AddEdge(v, u);
    for (int i = 1; i <= n; i++) Graph::vertex[i].u = i;
    Graph::DFS(1, 0);
    for (int i = 1; i <= k; i++) ans += q.top(), q.pop();
    printf("%lld\n", ans);
    return 0;
}