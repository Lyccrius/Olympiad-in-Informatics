#include <cstdio>
#include <algorithm>

const int maxN = 100000 + 10;

int n;
int u, v, w;

struct Trie {
    struct Node {
        int next[2];
    } node[maxN << 5];

    int cnt;

    void Insert(int val) {
        int u = 0;
        for (int i = 30; i >= 0; i--) {
            bool v = (val >> i) & 1;
            if (node[u].next[v] == 0) node[u].next[v] = ++cnt;
            u = node[u].next[v];
        }
        return;
    }

    int Search(int val) {
        int res = 0;
        int u = 0;
        for (int i = 30; i >= 0; i--) {
            bool v = (val >> i) & 1;
            if (node[u].next[!v]) {
                res += 1 << i;
                u = node[u].next[!v];
            } else u = node[u].next[v];
        }
        return res;
    }
} trie;

namespace Graph {
    struct Vertex {
        int dist;
        int head;
    } vertex[maxN];

    struct Edge {
        int head;
        int next;
        int weight;
    } edge[maxN << 1];

    int ecnt;
    
    void AddEdge(int tail, int head, int weight) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        edge[ecnt].weight = weight;
        vertex[tail].head = ecnt;
        return;
    }

    void DFS(int u, int from) {
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            int w = edge[e].weight;
            if (v == from) continue;
            vertex[v].dist = vertex[u].dist ^ w;
            DFS(v, u);
        }
        return;
    }
}

int ans = 0;

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) scanf("%d%d%d", &u, &v, &w), Graph::AddEdge(u, v, w), Graph::AddEdge(v, u, w);
    Graph::DFS(1, 0);
    for (int i = 1; i <= n; i++) trie.Insert(Graph::vertex[i].dist);
    for (int i = 1; i <= n; i++) ans = std::max(ans, trie.Search(Graph::vertex[i].dist));
    printf("%d\n", ans);
    return 0;
}