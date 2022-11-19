#include <cstdio>
#include <algorithm>

const int inf = 1e9 + 10;
const int maxN = 100 + 10;

int n;

namespace Setting {
    struct Vertex {
        int head;
        int w;
        int size;
        int dis;
    };

    struct Edge {
        int head;
        int next;
    };

    Vertex vertex[maxN];
    Edge edge[maxN * 4];
    int ecnt;

    void AddEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    int ans = inf;
    int hospital;

    void DFS(int u, int from) {
        vertex[u].size = vertex[u].w;
        vertex[u].dis = 0;
        for (int i = vertex[u].head; i; i = edge[i].next) {
            int v = edge[i].head;
            if (v == from) continue;
            DFS(v, u);
            vertex[u].size += vertex[v].size;
            vertex[u].dis += vertex[v].dis + vertex[v].size;
        }
        if (!from && vertex[u].dis < ans) {
            ans = vertex[u].dis;
            hospital = u;
        }
        return;
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int w, u, v;
        scanf("%d%d%d", &w, &u, &v);
        Setting::vertex[i].w = w;
        if (u) {
            Setting::AddEdge(i, u);
            Setting::AddEdge(u, i);
        }
        if (v) {
            Setting::AddEdge(i, v);
            Setting::AddEdge(v, i);
        }
    }
    for (int i = 1; i <= n; i++) Setting::DFS(i, 0);
    printf("%d\n", Setting::ans);
    return 0;
}