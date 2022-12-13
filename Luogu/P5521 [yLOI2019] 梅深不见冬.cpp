#include <cstdio>
#include <vector>
#include <algorithm>

const int maxN = 1e5 + 4 + 10;

int n;
int p[maxN];
int w[maxN];

namespace Graph {
    struct Edge {
        int head;
        int dif;

        bool operator<(Edge other) const {
            return dif > other.dif;
        }
    };

    struct Vertex {
        std::vector<Edge> edge;
        int w;
        int ans;
    } vertex[maxN];

    int ecnt;

    void AddEdge(int tail, int head) {
        Edge e = {head};
        vertex[tail].edge.push_back(e);
        return;
    }

    void DFS(int u) {
        int res = 0;
        int sum = vertex[u].w;
        for (int i = 0; i < vertex[u].edge.size(); i++) {
            int v = vertex[u].edge[i].head;
            DFS(v);
            vertex[u].edge[i].dif = vertex[v].ans - vertex[v].w;
            sum += vertex[v].w;
        }
        std::sort(vertex[u].edge.begin(), vertex[u].edge.end());
        res = sum;
        sum = 0;
        for (int i = 0; i < vertex[u].edge.size(); i++) {
            int v = vertex[u].edge[i].head;
            res = std::max(res, sum + vertex[v].ans);
            sum += vertex[v].w;
        }
        vertex[u].ans = res;
        return;
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 2; i <= n; i++) scanf("%d", &p[i]);
    for (int i = 1; i <= n; i++) scanf("%d", &w[i]);
    for (int i = 2; i <= n; i++) Graph::AddEdge(p[i], i);
    for (int i = 1; i <= n; i++) Graph::vertex[i].w = w[i];
    Graph::DFS(1);
    for (int i = 1; i <= n; i++) printf("%d ", Graph::vertex[i].ans);
    printf("\n");
    return 0;
}