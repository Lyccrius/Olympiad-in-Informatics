#include <cstdio>
#include <algorithm>

const int maxN = 5e5;

int N;
int S;
int a, b, t;

long long V;

namespace Graph {
    struct Vertex {
        int head;
        int weight;
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int weight;
        int next;
    } edge[maxN * 2 + 10];

    int ecnt;

    void AddEdge(int tail, int head, int weight) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].weight = weight;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    void DFS(int u, int from) {
        for (int e = vertex[u].head; e; e = edge[e].next) if (edge[e].head != from) DFS(edge[e].head, u);
        for (int e = vertex[u].head; e; e = edge[e].next) if (edge[e].head != from) vertex[u].weight = std::max(vertex[u].weight, vertex[edge[e].head].weight + edge[e].weight);
        for (int e = vertex[u].head; e; e = edge[e].next) if (edge[e].head != from) V += vertex[u].weight - (vertex[edge[e].head].weight + edge[e].weight);
        return;
    }
}

int main() {
    scanf("%d", &N);
    scanf("%d", &S);
    for (int i = 1; i < N; i++) scanf("%d%d%d", &a, &b, &t), Graph::AddEdge(a, b, t), Graph::AddEdge(b, a, t);
    Graph::DFS(S, 0);
    printf("%lld\n", V);
    return 0;
}